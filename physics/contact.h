#ifndef CONTACT_H
#define CONTACT_H

#include "collide_broad.h"

struct contact_t : potential_collision_t
{
    Vector3 point;
    Vector3 normal;
    real penetration;
};
typedef std::vector<contact_t> contacts_t;

void check_contact(const potential_collision_t &contact, contacts_t &contacts)
{
    for (const Vector3 vertex : contact.rb->cube.vertices)
    {
        const real penetration = -dist_to_plane(vertex, *contact.plane);
        if (penetration >= 0) {
            contact.rb->ignore = true;
            contacts.push_back(contact_t{contact.rb, contact.plane, vertex, contact.plane->normal, penetration});
        }
    }
}

contacts_t get_contacts(const potential_collisions_t &potential_contacts)
{
    contacts_t contacts;
    for (const potential_collision_t &potential_contact : potential_contacts)
    {
        const real dist = dist_to_plane(potential_contact.rb->transform.position, *potential_contact.plane);
        if (dist_to_plane(potential_contact.rb->transform.position, *potential_contact.plane) <= potential_contact.rb->radius)
            check_contact(potential_contact, contacts);
    }
    return contacts;
}

#endif // ! CONTACT_H