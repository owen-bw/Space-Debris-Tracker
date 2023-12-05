#include <vector>
#include <cmath>

#pragma once

using namespace std;

struct SpaceDebris {

    int intId;

    int id;

    double x, y, z;

    SpaceDebris(int id, double x, double y, double z)
        : id(id), x(x), y(y), z(z) {}

    double distance(const SpaceDebris &other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
    }
};

class Octree {

public:

    Octree(const vector<SpaceDebris>& debris_list);

    vector<int> find_local_optimum(const SpaceDebris& start);

private:

    struct Node {

        unique_ptr<Node> children[8];

        vector<int> debris_ids;
    };

    unique_ptr<Node> root;

    vector<SpaceDebris> debris_list;

    void insert(Node* node, int debris_id, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max);

    int find_closest(const Node* node, const SpaceDebris& target, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max) const;

};

pair<int, int> find_local_optimum(const SpaceDebris& start, const vector<SpaceDebris>& debris_list);