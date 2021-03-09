#ifndef DEMOS_H
#define DEMOS_H

#include "physics/rigidbody.h"

#define RAND(min, max) ((real)rand() / RAND_MAX * (max - min) + min)

std::vector<RigidBody> create_rigidbodies(size_t count)
{
    std::vector<RigidBody> bodies(count);
    for (RigidBody &rb : bodies)
    {
        rb.transform.position = Vector3{0, 0, 0};
        rb.transform.rotation = Quaternion{1, 0, 0, 0};
        rb.iMass = 1;
        rb.cube = make_cube(1);
        rb.radius = magnetude(rb.cube.ref_vertices[0]);
        rb.lVelocity = normalize(Vector3{RAND(-1, 1), RAND(-1, 1), RAND(-1, 1)}) * 2;
        rb.aVelocity = normalize(Vector3{RAND(-1, 1), RAND(-1, 1), RAND(-1, 1)});
        rb.forceAccum = Vector3{0, 0, 0};
        rb.torqueAccum = Vector3{0, 0, 0};
        rb.iInertia = identity_matrix3;
        rb.iInertiaWorld = identity_matrix3;
        update_transform(rb.transform);
    }
    return bodies;
}

#endif // !DEMOS_H