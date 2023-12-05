#include <vector>
#include <cmath>

#pragma once

using namespace std;

struct SpaceDebris {

    int id;

    int riskyOther = -1;

    double riskDistance;

    double x, y, z;

    SpaceDebris(int id, double x, double y, double z)
        : id(id), x(x), y(y), z(z) {}

    double distance(const SpaceDebris &other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
    }
};

struct OctNode {

    OctNode* children[8] = {nullptr};

    vector<SpaceDebris> idList;

    //SpaceDebris debrisObject;
};

class Octree {

public:

    Octree(vector<SpaceDebris>& debris_list, double tolerance);

    void find_risky_debris(vector<SpaceDebris>& riskList);

private:

    OctNode* root;

    vector<SpaceDebris> debris_list;

    void insert(OctNode* node, SpaceDebris& debris, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double& tolerance);
    
    void find_risky(OctNode* node, vector<SpaceDebris>& riskList);
};

//vector<SpaceDebris> find_local_optimum(const SpaceDebris& start, const vector<SpaceDebris>& debris_list, double tolerance);

vector<SpaceDebris> find_local_optimum(vector<SpaceDebris>& debris_list, double tolerance, int powerIterations);