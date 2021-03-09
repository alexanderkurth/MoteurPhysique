#ifndef INIT_H
#define INIT_H

#include "../../include/SDL.h"
#include "glstuff.h"

SDL_Window *sdlWindow = NULL;
SDL_GLContext sdlContext;

int screen_width = 1200;
int screen_height = 800;

void start()
{
    // Start up SDL.
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create the display window and context.
    sdlWindow = SDL_CreateWindow("Math", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    sdlContext = SDL_GL_CreateContext(sdlWindow);
    SDL_GL_MakeCurrent(sdlWindow, sdlContext);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    // Start up glew.
    glewExperimental = GL_TRUE;
    glewInit();

    // Setup shader, render buffers and camera.
    useShader("shaders/colors.vs", "shaders/colors.fs");
    setupRendering();
    setupCamera(screen_width, screen_height);
    changeViewPoint(glm::vec3(15, 5, 0));
}

// Destroy buffers, window and context.
void clean()
{
    cleanRendering();
    SDL_GL_DeleteContext(sdlContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

#endif // !INIT_H