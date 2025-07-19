#pragma once
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "sdl/types.hh"

using f_pair = std::pair<float, float>;


namespace sdl
{
    class object
    {
    public:
        object( void ) = default;
        object( const f_pair &p_pos, const color &p_color );

        virtual ~object( void );


        virtual void draw( SDL_Renderer *p_render );
        virtual void get_events( events_container &p_events );

    protected:
        color m_color;

    private:
        std::vector<SDL_FPoint> m_points;
    };
} /* namespace sdl */