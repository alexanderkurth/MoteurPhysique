#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../utilities/utilities.h"
#include "primitive.h"
#include <vector>

struct Transform
{
    Vector3 position;
    Quaternion rotation;
    Matrix4 matrix;
};

inline Transform &update_transform(Transform &transform)
{
    transform.rotation = normalize(transform.rotation);
    transform.matrix = make_translate(transform.position) * make_matrix4(transform.rotation);
    return transform;
}

struct RigidBody
{
    Transform transform;
    real iMass;
    real radius;

    Vector3 lVelocity;
    Vector3 aVelocity;
    Vector3 forceAccum;
    Vector3 torqueAccum;
    Matrix3 iInertia;
    Matrix3 iInertiaWorld;
    real lDamping = .99;
    real aDamping = .99;

    Cube cube;

    // Stop caring about this rb after the first colision.
    bool ignore = false;
};
std::vector<RigidBody> bodies;

void integrate(RigidBody &body, real duration)
{
    /* Update the angular velocity. */ {
        Vector3 accel = body.iInertiaWorld * body.torqueAccum;
        body.aVelocity = (body.aVelocity + accel * duration) * real_pow(body.aDamping, duration);
        body.torqueAccum = {0, 0, 0};
    }

    /* Update the linear velocity. */ {
        Vector3 accel = body.forceAccum * body.iMass;
        body.lVelocity = (body.lVelocity + accel * duration) * real_pow(body.lDamping, duration);
        body.forceAccum = {0, 0, 0};
    }

    /* Update the position and rotation. */ {
        body.transform.position = body.transform.position + (body.lVelocity * duration);
        body.transform.rotation = body.transform.rotation + (body.aVelocity * duration);
    }

    // Update the transform matrix.
    update_transform(body.transform);
    transform_cube(body.cube, body.transform.matrix);

    // Update the inverse inertia tensor world.
    const Matrix3 rotation = make_matrix3(body.transform.rotation);
    body.iInertiaWorld = rotation * body.iInertia * transposed(rotation);
}

void stop_integrating(RigidBody &rb)
{
    /* Stop linear motion. */
    rb.forceAccum = Vector3{0, 0, 0};
    rb.lVelocity = Vector3{0, 0, 0};

    /* Stop angular motion. */
    rb.torqueAccum = Vector3{0, 0, 0};
    rb.aVelocity = Vector3{0, 0, 0};
}

/* Apply a force to the given point (in world corrdinates). */
void add_world_force(RigidBody &body, const Vector3 &force, const Vector3 &world)
{
    Vector3 point = world - body.transform.position;
    body.forceAccum = body.forceAccum + force;
    body.torqueAccum = body.torqueAccum + vec_product(point, force);
}

/* Apply a force to the given point (in local coordinates). */
void add_local_force(RigidBody &body, const Vector3 &force, const Vector3 &local)
{
    Vector3 point = local_point_to_world(body.transform.matrix, local);
    add_world_force(body, force, point);
}

/* Return a vector containing a pointer to each rigidbody. */
std::vector<RigidBody *> get_rigidbody_list()
{
    std::vector<RigidBody *> list;
    list.reserve(bodies.size());
    for (RigidBody &body : bodies)
    {
        if (body.ignore == false)
            list.push_back(&body);
    }
    return list;
}

#endif // !RIGIDBODY_H