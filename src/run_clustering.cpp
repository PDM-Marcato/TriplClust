//////////////////////////////////////////////////////////
// Run Clustering Class
// J.C. Zamora, zamora@frib.msu.edu
// FRIB, 2025
//////////////////////////////////////////////////////////
#include <stdint.h>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

#include "run_clustering.h"



Run_clustering::Run_clustering(){

	opt_params =  new Opt();

}

Run_clustering::~Run_clustering(){

	delete opt_params;
        vID.clear();
	//delete cloud_xyz;
	//delete cloud_xyz_smooth;

}


void Run_clustering::Init(vector<double> v1, vector<double> v2, vector<double> v3, bool isordered){

        cloud_xyz.setOrdered(isordered);
        Point ponto;
        const size_t len = v1.size();
    	for(int i=0;i<len;i++){
                ponto.x = v1[i];
                ponto.y = v2[i];
                ponto.z = v3[i];
                ponto.index = i;
                cloud_xyz.push_back(ponto);        
        }
        



}

vector<int> Run_clustering::GetIDs(){

        return vID;

}


void Run_clustering::Solve(){


         int opt_verbose = opt_params->get_verbosity();
         //bool opt_ordered = opt_params->get_ordered();


         // load data        
        
        
        if (cloud_xyz.size() == 0) {
                std::cerr << "[Error] empty cloud in file "<< std::endl;
                //return 1;
                }


        // compute characteristic length dnn if needed
        if (opt_params->needs_dnn()) {
                double dnn = std::sqrt(first_quartile(cloud_xyz));
                if (opt_verbose > 0) {
                std::cout << "[Info] computed dnn: " << dnn << std::endl;
                }
                opt_params->set_dnn(dnn);
                if (dnn == 0.0) {
                        std::cerr << "[Error] dnn computed as zero. "
                        << "Suggestion: remove doublets, e.g. with 'sort -u'"
                        << std::endl;
                        //return 2;
                        }
                }

           // Step 1) smoothing by position averaging of neighboring points          
          smoothen_cloud(cloud_xyz, cloud_xyz_smooth, opt_params->get_r());

          if (opt_verbose > 1) {
            bool rc;
            rc = cloud_to_csv(cloud_xyz_smooth);
            if (!rc)
              std::cerr << "[Error] can't write debug_smoothed.csv" << std::endl;
            
          }


          // Step 2) finding triplets of approximately collinear points
          std::vector<triplet> triplets;
          generate_triplets(cloud_xyz_smooth, triplets, opt_params->get_k(),
                            opt_params->get_n(), opt_params->get_a());


        // Step 3) single link hierarchical clustering of the triplets
          cluster_group cl_group;
          compute_hc(cloud_xyz_smooth, cl_group, triplets, opt_params->get_s(),
                     opt_params->get_t(), opt_params->is_tauto(), opt_params->get_dmax(),
                     opt_params->is_dmax(), opt_params->get_linkage(), opt_verbose);

          // Step 4) pruning by removal of small clusters ...
          cleanup_cluster_group(cl_group, opt_params->get_m(), opt_verbose);
          cluster_triplets_to_points(triplets, cl_group);
        // .. and (optionally) by splitting up clusters at gaps > dmax
          if (opt_params->is_dmax()) {
            cluster_group cleaned_up_cluster_group;
            for (cluster_group::iterator cl = cl_group.begin(); cl != cl_group.end();
                 ++cl) {
              max_step(cleaned_up_cluster_group, *cl, cloud_xyz, opt_params->get_dmax(),
                       opt_params->get_m() + 2);
            }
            cl_group = cleaned_up_cluster_group;
          }


        // store cluster labels in points
          add_clusters(cloud_xyz, cl_group, opt_params->is_gnuplot());

        // store IDs in a vector
        vID = get_clusterID(cloud_xyz);

}





