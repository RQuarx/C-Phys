#pragma once
#include <functional>
#include <SDL3/SDL_render.h>


namespace sdl
{
    enum app_retval
    {
        RETURN_CONTINUE,
        RETURN_SKIP,
        RETURN_FAILURE,
        RETURN_SUCCESS,
    };


    struct event_data
    {
        SDL_Window   *window;
        SDL_Renderer *render;

        SDL_Event *event;
    };


    using event_func = std::function<app_retval (event_data &)>;
    using events_container =
        std::unordered_map<uint32_t, std::vector<event_func>>;


    struct color
    {
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 0;

        color( const float &p_all ) :
            r(p_all), g(p_all), b(p_all), a(p_all)
        {}

        color( const SDL_FColor &p_color ) :
            r(p_color.r), g(p_color.g), b(p_color.b), a(p_color.a)
        {}

        color( float p_r, float p_g, float p_b, float p_a ) :
            r(p_r), g(p_g), b(p_b), a(p_a)
        {}

        color( float p_r, float p_g, float p_b ) :
            r(p_r), g(p_g), b(p_b), a(1)
        {}

        color( void ) = default;

        auto
        operator==( const color &p_color ) const noexcept -> bool
        {
            if (p_color.r != r) return false;
            if (p_color.g != g) return false;
            if (p_color.b != b) return false;
            if (p_color.a != a) return false;
            return true;
        }
    };
}  /* namespace sdl */