//////////////////////////////////////////////////////////
// Run Clustering Class
// J.C. Zamora, zamora@frib.msu.edu
// FRIB, 2025
//////////////////////////////////////////////////////////
#ifndef Run_clustering_H
#define Run_clustering_H


#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "cluster.h"
#include "dnn.h"
#include "graph.h"
#include "option.h"
#include "output.h"
#include "pointcloud.h"

using namespace std;

class Run_clustering
{
  public:
  Run_clustering();
  ~Run_clustering();

  //void Reset();
  void Init(vector<double> v1, vector<double> v2, vector<double> v3, bool isordered);
  void Solve();
  vector<int> GetIDs();

 

 private:
 vector<double> vX, vY, vZ;
 vector<int> vID;
 Opt* opt_params;
 PointCloud cloud_xyz;
 PointCloud cloud_xyz_smooth;
  
 };
  
#endif
