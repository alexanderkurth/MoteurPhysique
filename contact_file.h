#ifndef CONTACT_FILE_H
#define CONTACT_FILE_H

#include "physics/contact.h"
#include <fstream>
#include <string>

std::ofstream file;
std::string file_buffer;

void write_contact(const contact_t &contact, size_t no)
{
    file_buffer.append("\n-------------------------------------\n" + std::to_string(no) + " : ");

    std::stringstream ss_rb;
    ss_rb << contact.rb;
    file_buffer.append("\n\nRigidBody : " + ss_rb.str());

    std::stringstream ss_pl;
    ss_pl << contact.plane;
    file_buffer.append("\nPlane : " + ss_pl.str());

    file_buffer.append("\nPoint : (" + std::to_string(contact.point.x) + ", " + std::to_string(contact.point.y) + ", " + std::to_string(contact.point.z) + ")");
    file_buffer.append("\nNormal : (" + std::to_string(contact.normal.x) + ", " + std::to_string(contact.normal.y) + ", " + std::to_string(contact.normal.z) + ")");
    file_buffer.append("\nPenetration : " + std::to_string(contact.penetration));
}

void write_contacts(const contacts_t& contacts) {
    file.open("contacts.txt", std::ofstream::trunc);
    size_t i=0;
    for (const contact_t& contact : contacts) {
        write_contact(contact, i++);
    }
    file << file_buffer;
    file_buffer = "";
    file.close();
}

#endif // !CONTACT_FILE_H