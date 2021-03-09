#ifndef TREE_H
#define TREE_H

#include "rigidbody.h"

const size_t max_count = 4;
const size_t max_depth = 2;

/* Holds the informations about a node within the octree.
   A single node can itself be the root of the tree. */
struct oc_tree_t
{
    Vector3 center;                     // Center point of the node in world coordinates.
    real half_width;                    // Half the width of the node (aka. from center to edge).
    std::vector<RigidBody *> rb_list;   // List of rigid bodies within the node.
    std::vector<Plane *> plane_list;    // List of planes within the node.
    std::vector<oc_tree_t> children;    // List of child node if any.
};

/* Fills the node with the contained rigid bodies from the provided list. */
void populate_node(oc_tree_t &node, const std::vector<RigidBody *> &list)
{
    for (RigidBody *rb : list) // for all rb.
    {
        // Check if the spherical bounding volume of the rb enters the node.
        if (real_abs(node.center.x - rb->transform.position.x) - rb->radius <= node.half_width &&
            real_abs(node.center.y - rb->transform.position.y) - rb->radius <= node.half_width &&
            real_abs(node.center.z - rb->transform.position.z) - rb->radius <= node.half_width)
        {
            // Add the rb to the node.
            node.rb_list.push_back(rb);
        }
    }
}

/* Fills the node withthe contained planes form the provided list. */
void populate_node(oc_tree_t &node, const std::vector<Plane *> &list)
{
    for (Plane *plane : list) // for all planes
    {
        // Check if the plane enters the node.
        if (dist_to_plane(node.center, *plane) <= node.half_width)
        {
            // Add the plane to this node.
            node.plane_list.push_back(plane);
        }
    }
}

/* Recursively update the tree and create child nodes as need to keep
   the number of items within a node under the provided limit. */
void update_tree_recursive(oc_tree_t &tree, size_t depth)
{
    // Is the number of item within the node under the limit?
    // Is the depth of the node in the tree over the limit?
    if (tree.rb_list.size() + tree.plane_list.size() <= max_count || depth > max_depth)
        return;

    // Create 8 child nodes and divide the contained items.
    const real new_half = tree.half_width / 2;
    for (size_t i = 0; i < 8; i++)
    {   
        // Find node position from node index.
        real x = (i & 1) ? -new_half : new_half;
        real y = (i & 2) ? -new_half : new_half;
        real z = (i & 4) ? -new_half : new_half;

        // Create child node, populate it and recall this function on the node.
        tree.children.push_back(oc_tree_t{tree.center + Vector3{x, y, z}, new_half});
        populate_node(tree.children.back(), tree.rb_list);
        populate_node(tree.children.back(), tree.plane_list);
        update_tree_recursive(tree.children.back(), depth + 1);
    }
    // Clear the item within this node as they are now within the child nodes.
    tree.rb_list.clear();
    tree.plane_list.clear();
}

#endif // !TREE_H