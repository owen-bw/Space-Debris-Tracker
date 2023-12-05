/****************************************************************/
/*                      SpaceDebris Algorithms                  */
/*                                                              */
/*            Blake Owen, Bryant Woolsey, Marco Wehrhahn        */
/*                                                              */
/*        This source code contains the two algorithms we       */
/*        developed for solving the risk assessment for         */
/*        satellite and debris data read from TLE files.        */
/****************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <utility>
#include <bitset>

#include "SpaceDebris.h"

using namespace std;

// Octree solution
Octree::Octree(vector<SpaceDebris>& debris_list, double tolerance) {
    this->debris_list = debris_list;

    OctNode* newRoot = new OctNode();

    root = newRoot;

    double min_x, min_y, min_z, max_x, max_y, max_z;

    min_x = min_y = min_z = numeric_limits<double>::max();

    max_x = max_y = max_z = numeric_limits<double>::lowest();
    
    for (const auto& debris : debris_list) {

        min_x = min(min_x, debris.x);

        max_x = max(max_x, debris.x);

        min_y = min(min_y, debris.y);

        max_y = max(max_y, debris.y);

        min_z = min(min_z, debris.z);

        max_z = max(max_z, debris.z);
    }

    for (int i = 0; i < debris_list.size(); i++) {
      insert(root, debris_list.at(i), min_x, max_x, min_y, max_y, min_z, max_z, tolerance);
    }
}

void Octree::insert(OctNode* node, SpaceDebris& debris, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double& tolerance) {

    if (x_max - x_min <= tolerance) {
      node->idList.push_back(debris);
      return;
    }

    double x_mid = (x_min + x_max) / 2;

    double y_mid = (y_min + y_max) / 2;

    double z_mid = (z_min + z_max) / 2;

    int child_index = 0;

    bitset<3> quadrant = {0};

    if (debris.x > x_mid)
      quadrant[0] = 1;
    if (debris.y > y_mid)
      quadrant[1] = 1;
    if (debris.z > z_mid)
      quadrant[2] = 1;

    child_index = quadrant.to_ulong();

    if (!node->children[child_index]) {
      node->children[child_index] = new OctNode();
    }

    double new_x_min = quadrant[0] ? x_mid : x_min;
        double new_x_max = quadrant[0] ? x_max : x_mid;
        double new_y_min = quadrant[1] ? y_mid : y_min;
        double new_y_max = quadrant[1] ? y_max : y_mid;
        double new_z_min = quadrant[2] ? z_mid : z_min;
        double new_z_max = quadrant[2] ? z_max : z_mid;

    insert(node->children[child_index], debris, new_x_min, new_x_max, new_y_min, new_y_max, new_z_min, new_z_max, tolerance);
}

void Octree::find_risky(OctNode* node, vector<SpaceDebris>& riskList) {
  if (node == nullptr) {
    return;
  } else if (node->idList.size() > 1) {
    for (int i = 0; i < node->idList.size() - 1; i++) {
      node->idList.at(i).riskyOther = node->idList.at(i + 1).id;
      node->idList.at(i).riskDistance = node->idList.at(i).distance(node->idList.at(i + 1));
      riskList.push_back(node->idList.at(i));
    }
  }

  for (int i = 0; i < 8; i++) {
    find_risky(node->children[i], riskList);
  }
}

void Octree::find_risky_debris(vector<SpaceDebris>& riskList) {
  find_risky(root, riskList);
}

// Iterative solution
vector<SpaceDebris> find_local_optimum(vector<SpaceDebris>& debris_list, double tolerance, int iterations) {
    vector<SpaceDebris> result;
    for (int p = 1; p <= iterations; p++) {
      for (int i = 0; i < debris_list.size() - p; i += p) {
        double dist = debris_list.at(i).distance(debris_list.at(i + 1));
        if (dist <= tolerance) {
          debris_list.at(i).riskyOther = debris_list.at(i + 1).id;
          debris_list.at(i).riskDistance = dist;
          result.push_back(debris_list.at(i));
        }
      }
    }
    
    return result;

}

bool compareDebrisDistanceLess(SpaceDebris d1, SpaceDebris d2) {
    return (d1.riskDistance < d2.riskDistance);
}

bool compareDebrisDistanceGreater(SpaceDebris d1, SpaceDebris d2) {
    return (d1.riskDistance > d2.riskDistance);
}

bool compareDebrisIdLess(SpaceDebris d1, SpaceDebris d2) {
    return (d1.id < d2.id);
}

bool compareDebrisIdGreater(SpaceDebris d1, SpaceDebris d2) {
    return (d1.id > d2.id);
}