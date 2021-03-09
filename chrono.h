#ifndef _CHRONO_H_
#define _CHRONO_H_

#include "../include/SDL.h"
#include "utilities/precision.h"

/* Provide a frame rate limiter. Frames per second cannot exceed this amount. */
#define LIMIT_FPS_TO 60

/* Stopwatch to get frame time. */
struct chrono_t {
    size_t end = SDL_GetTicks (); // End of last frame in milli-seconds.
    real time = 0; // Time of last frame in seconds.

    /* Update the time for a new frame. */
    inline void update () {
        size_t milli = SDL_GetTicks () - end;
#if LIMIT_FPS_TO == 0
        time = static_cast <real> (milli) / 1000;
#else
        const size_t max_milli = 1000 / LIMIT_FPS_TO;
        SDL_Delay ((max_milli > milli) * (max_milli - milli));
        time = static_cast <real> (_MAX (max_milli, milli)) / 1000;
#endif
        end = SDL_GetTicks ();
    }
} chrono;

#endif // !_CHRONO_H_