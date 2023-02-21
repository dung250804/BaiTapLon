#ifndef UTILITIES_H
#define UTILITIES_H

#pragma once
#include<SDL.h>

namespace utils
{
    inline float HireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001f;

        return t;
    }
}

class Utilities
{
    public:
        Utilities();
        virtual ~Utilities();

    protected:

    private:
};

#endif // UTILITIES_H
