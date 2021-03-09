#include "chrono.h"
#include "render/init.h"
#include "demos.h"
#include "contact_file.h"
#include <time.h>

bool quit = false;

void handle_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                SDL_GetWindowSize(sdlWindow, &screen_width, &screen_height);
                break;
            }
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;

            case SDLK_1: // Camera pos:
                changeViewPoint(glm::vec3(20, 0, 0));
                break;

            case SDLK_2: // Camera pos:
                changeViewPoint(glm::vec3(0, 0, 20));
                break;

            case SDLK_3: // Camera pos:
                changeViewPoint(glm::vec3(-20, 0, 0));
                break;

            case SDLK_4: // Camera pos:
                changeViewPoint(glm::vec3(0, 0, -20));
                break;
            }
        }
    }
}

// Independant operations to do each frame.
inline void frame()
{
    // Swap rendering buffers for openGL.
    glViewport(0, 0, screen_width, screen_height);
    SDL_GL_SwapWindow(sdlWindow);
}

int main(int argc, char *argv[])
{
    start();
    srand(clock());

    contacts_t contacts;

    bodies = create_rigidbodies(100);
    planes = make_walls(6);

    // render loop
    while (!quit)
    {
        // Update the frame time.
        chrono.update();

        // Handle any triggered event (key stroke).
        handle_event();

        // Clear the rendering buffer.
        glClearColor(.1, .1, .1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderPlane(Vector3{0, 0, 0});

        for (RigidBody &rb : bodies)
        {
            integrate(rb, chrono.time);
            renderBody(rb);
        }

        /* Collisions stuff goes here! */
        potential_collisions_t potential_collisions = get_potential_collisions(Vector3{0, 0, 0}, 7);
        contacts_t real_collisions = get_contacts(potential_collisions);

        /* Show detected collisions on screen. */
        for (const contact_t &contact : real_collisions)
        {
            contacts.push_back(contact);
            stop_integrating(*contact.rb);
            write_contacts(contacts);
        }

        for (const contact_t contact : contacts)
        {
            renderPoint(contact.point);
        }

        // Swap rendering buffers for openGL.
        glViewport(0, 0, screen_width, screen_height);
        SDL_GL_SwapWindow(sdlWindow);
    }

    clean();
    return 0;
}