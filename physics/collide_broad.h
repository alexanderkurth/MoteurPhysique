#ifndef COLLIDE_BROAD_H
#define COLLIDE_BROAD_H

#include "tree.h"

/* Holds the information about a potential collision. 
   Only cares about rigid body to plane collision. */
struct potential_collision_t
{
    RigidBody *rb;
    Plane *plane;
};
/* Short-hand for a vector of potential collisions. */
typedef std::vector<potential_collision_t> potential_collisions_t;

/* Check if the potential collision already exist withing the provided vector. */
bool exist(const potential_collisions_t &vec, const potential_collision_t &item)
{
    for (const potential_collision_t &i : vec) // for all potential collisions.
    {
        // Are both the potential collision identical?
        if (i.rb == item.rb && i.plane == item.plane)
            return true;
    }
    return false;
}

/* Recursively find the potential collisions withing a node and its children. */
void get_potential_collisions_recursive(const oc_tree_t &node, potential_collisions_t &collisions)
{
    for (size_t i = 0; i < node.rb_list.size(); i++) // for all rigid body in node.
        for (size_t j = 0; j < node.plane_list.size(); j++) // for all planes in node.
        {
            // Does that collision already exist?
            const potential_collision_t pc{node.rb_list[i], node.plane_list[j]};
            if (!exist(collisions, pc))
                // Add the collision to the vector of potential collisions.
                collisions.push_back(pc);
        }

    for (size_t i = 0; i < node.children.size(); i++) // for all child node.
        get_potential_collisions_recursive(node.children[i], collisions);
}

/* Create the octree containing all the game items and evaluate the potential collisions. */
potential_collisions_t get_potential_collisions(const Vector3 &center, real half_width)
{
    // Create the octree.
    oc_tree_t tree{center, half_width, get_rigidbody_list(), get_plane_list()};
    update_tree_recursive(tree, 0);

    // Find the potential collisions.
    potential_collisions_t collisions;
    get_potential_collisions_recursive(tree, collisions);
    return collisions;
}

#endif