#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "rigidbody.h"
#include <vector>

struct Cube
{
    Vector3 ref_vertices[8];
    Vector3 vertices[8];
};

constexpr Cube make_cube(real size)
{
    return Cube{
        Vector3{size / 2, size / 2, size / 2},    //0
        Vector3{size / 2, size / 2, -size / 2},   //1
        Vector3{size / 2, -size / 2, -size / 2},  //2
        Vector3{size / 2, -size / 2, size / 2},   //3
        Vector3{-size / 2, size / 2, size / 2},   //4
        Vector3{-size / 2, size / 2, -size / 2},  //5
        Vector3{-size / 2, -size / 2, -size / 2}, //6
        Vector3{-size / 2, -size / 2, size / 2}}; //7
}

constexpr void transform_cube(Cube &cube, const Matrix4 &transform)
{
    cube.vertices[0] = transform_point(transform, cube.ref_vertices[0]);
    cube.vertices[1] = transform_point(transform, cube.ref_vertices[1]);
    cube.vertices[2] = transform_point(transform, cube.ref_vertices[2]);
    cube.vertices[3] = transform_point(transform, cube.ref_vertices[3]);
    cube.vertices[4] = transform_point(transform, cube.ref_vertices[4]);
    cube.vertices[5] = transform_point(transform, cube.ref_vertices[5]);
    cube.vertices[6] = transform_point(transform, cube.ref_vertices[6]);
    cube.vertices[7] = transform_point(transform, cube.ref_vertices[7]);
}

struct Plane
{
    Vector3 position;
    Vector3 normal; // unit vector
};
std::vector<Plane> planes;

std::vector<Plane> make_walls(real half_width)
{
    std::vector<Plane> planes(6);
    planes[0] = Plane{Vector3{half_width, 0, 0}, Vector3{-1, 0, 0}};
    planes[1] = Plane{Vector3{-half_width, 0, 0}, Vector3{1, 0, 0}};
    planes[2] = Plane{Vector3{0, half_width, 0}, Vector3{0, -1, 0}};
    planes[3] = Plane{Vector3{0, -half_width, 0}, Vector3{0, 1, 0}};
    planes[4] = Plane{Vector3{0, 0, half_width}, Vector3{0, 0, -1}};
    planes[5] = Plane{Vector3{0, 0, -half_width}, Vector3{0, 0, 1}};
    return planes;
}

/* Return a list of pointer to all the planes. */
std::vector<Plane *> get_plane_list()
{
    std::vector<Plane *> plane_list;
    plane_list.reserve(planes.size());
    for (Plane &plane : planes) // for all planes
    {
        // Add pointer to plane.
        plane_list.push_back(&plane);
    }
    return plane_list;
}

/* Find the shortest distance between a point and a plane. */
constexpr real dist_to_plane(const Vector3 &point, const Plane &plane)
{
    return scalar_product(point - plane.position, plane.normal);
}

#endif // !PRIMITIVE_H