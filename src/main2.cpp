#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <string>


#include "run_clustering.h"



using namespace std;



//int main(int argc, char **argv) {
int main() {

        //--------------------
                string FileName   = "test2.dat" ;
                ifstream file(FileName);
                string line;


                vector<double>  vX;
                vector<double>  vY;
                vector<double>  vZ;
                double a, b, c;

                while (!file.eof()) {
                        getline(file,line);
                        if (line.length() != 0 ){
                                istringstream ss(line);
                                ss >> a;
                                ss >> b;
                                ss >> c;
                                vX.push_back(a);
                                vY.push_back(b);
                                vZ.push_back(c);
                        }                 

                      

                }




         Run_clustering clusters;
         clusters.Init(vX,vY,vZ, 1);
         clusters.Solve();
         vector<int> clustIDs = clusters.GetIDs();
         
        for(int i=0; i<vX.size(); i++){
                cout<<vX[i]<<"  "<<vY[i]<<"  "<<vZ[i]<<"  "<<clustIDs[i]<<endl;

                }


  return 0;
}
