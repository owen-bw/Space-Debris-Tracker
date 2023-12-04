#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <memory>

#include "SpaceDebris.h"

using namespace std;

Octree::Octree(const vector<SpaceDebris>& debris_list) : debris_list(debris_list) {

    root = make_unique<Node>();

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

    for (int i = 0; i < debris_list.size(); ++i) {

        insert(root.get(), i, min_x, max_x, min_y, max_y, min_z, max_z);

    }
}

void Octree::insert(Node* node, int debris_id, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max) {

    const SpaceDebris& debris = debris_list[debris_id];

    if (x_max - x_min <= 1 && y_max - y_min <= 1 && z_max - z_min <= 1) {

        node->debris_ids.push_back(debris_id);

        return;
    }

    double x_mid = (x_min + x_max) / 2;

    double y_mid = (y_min + y_max) / 2;

    double z_mid = (z_min + z_max) / 2;

    int child_index = 0;

    if (debris.x > x_mid) child_index |= 1, x_min = x_mid; else x_max = x_mid;

    if (debris.y > y_mid) child_index |= 2, y_min = y_mid; else y_max = y_mid;

    if (debris.z > z_mid) child_index |= 4, z_min = z_mid; else z_max = z_mid;

    if (!node->children[child_index]) {

        node->children[child_index] = make_unique<Node>();

    }

    insert(node->children[child_index].get(), debris_id, x_min, x_max, y_min, y_max, z_min, z_max);

}

int Octree::find_closest(const Node* node, const SpaceDebris& target, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max) const {

    if (!node) return -1;

    double x_mid = (x_min + x_max) / 2;

    double y_mid = (y_min + y_max) / 2;

    double z_mid = (z_min + z_max) / 2;

    int child_index = 0;

    if (target.x > x_mid) child_index |= 1, x_min = x_mid; else x_max = x_mid;

    if (target.y > y_mid) child_index |= 2, y_min = y_mid; else y_max = y_mid;

    if (target.z > z_mid) child_index |= 4, z_min = z_mid; else z_max = z_mid;

    int closest = -1;

    double min_distance = numeric_limits<double>::max();

    for (int debris_id : node->debris_ids) {

        double dist = target.distance(debris_list[debris_id]);

        if (dist < min_distance) {

            min_distance = dist;

            closest = debris_id;

        }

    }

    for (int i = 0; i < 8; ++i) {

        if (i == child_index) continue;

        double dx = max(max(x_min - target.x, 0.0), target.x - x_max);

        double dy = max(max(y_min - target.y, 0.0), target.y - y_max);

        double dz = max(max(z_min - target.z, 0.0), target.z - z_max);


        if (dx * dx + dy * dy + dz * dz < min_distance) {

            int candidate = find_closest(node->children[i].get(), target, x_min, x_max, y_min, y_max, z_min, z_max);

            if (candidate != -1) {

                double dist = target.distance(debris_list[candidate]);

                if (dist < min_distance) {

                    min_distance = dist;

                    closest = candidate;

                }

            }

        }

    }

    return closest;

}

vector<int> Octree::find_local_optimum(const SpaceDebris& start) {

    vector<int> result;

    SpaceDebris current = start;

    while (true) {

        int closest_index = find_closest(root.get(), current, 0, 1, 0, 1, 0, 1);

        if (closest_index == -1) break;

        result.push_back(debris_list[closest_index].id);

        current = debris_list[closest_index];

    }

    return result;
}

/*
int main() { //Modify to allow user to select input tied to Blake's GUI

    vector<SpaceDebris> debris_list = {

        {1, 2.0, 3.0, 1.0},

        {2, 5.0, 1.0, 3.0},

        {3, 4.0, 6.0, 7.0},

        {4, 9.0, 2.0, 5.0},

        {5, 6.0, 8.0, 1.0},

    };

    SpaceDebris start(0, 1.0, 1.0, 1.0);

    Octree octree(debris_list);

    vector<int> local_optimum_octree = octree.find_local_optimum(start);

    cout << "Octree: ";

    for (int id : local_optimum_octree) {

        cout << id << " ";

    }

    cout << endl;

    // vector<int> local_optimum_greedy = find_local_optimum(start, debris_list);

    // cout << "Greedy: ";

    // for (int id : local_optimum_greedy) {

    //     cout << id << " ";

    // }

    // cout << endl;

    return 0;
}
*/