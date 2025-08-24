#pragma once
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "sdl/types.hh"


namespace sdl
{
    class Object
    {
    public:
        Object( void ) = default;
        Object( const f_pair &p_pos, const Color &p_color );

        virtual ~Object( void ) = 0;


        virtual void draw( SDL_Renderer *p_render ) = 0;
        virtual void get_events( events_container &p_events ) = 0;

    protected:
        Color m_color;

    private:
        std::vector<SDL_FPoint> m_points;
    };
} /* namespace sdl */