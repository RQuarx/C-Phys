#pragma once
#include <functional>
#include <SDL3/SDL_render.h>

using f_pair = std::pair<float, float>;


namespace sdl
{
    enum AppReturn
    {
        RETURN_CONTINUE,
        RETURN_SKIP,
        RETURN_FAILURE,
        RETURN_SUCCESS,
    };


    struct EventData
    {
        SDL_Window   *window;
        SDL_Renderer *render;

        SDL_Event *event;
    };


    using event_func = std::function<AppReturn (EventData &)>;
    using events_container =
        std::unordered_map<uint32_t, std::vector<event_func>>;


    struct Color
    {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        uint8_t a = 0;

        Color( const uint8_t &p_all ) :
            r(p_all), g(p_all), b(p_all), a(p_all)
        {}

        Color( const SDL_FColor &p_color ) :
            r(p_color.r), g(p_color.g), b(p_color.b), a(p_color.a)
        {}

        Color( uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a ) :
            r(p_r), g(p_g), b(p_b), a(p_a)
        {}

        Color( uint8_t p_r, uint8_t p_g, uint8_t p_b ) :
            r(p_r), g(p_g), b(p_b), a(1)
        {}

        Color( void ) = default;

        auto
        operator==( const Color &p_color ) const noexcept -> bool
        {
            if (p_color.r != r) return false;
            if (p_color.g != g) return false;
            if (p_color.b != b) return false;
            if (p_color.a != a) return false;
            return true;
        }
    };
}  /* namespace sdl */


constexpr inline auto
operator""_rgb( unsigned long long val ) -> sdl::Color
{
    return sdl::Color {
        static_cast<uint8_t>((val >> 16) & 0xFF),
        static_cast<uint8_t>((val >> 8) & 0xFF),
        static_cast<uint8_t>(val & 0xFF)
    };
}


constexpr inline auto
operator""_rgba( unsigned long long val ) -> sdl::Color
{
    return sdl::Color {
        static_cast<uint8_t>((val >> 24) & 0xFF),
        static_cast<uint8_t>((val >> 16) & 0xFF),
        static_cast<uint8_t>((val >> 8) & 0xFF),
        static_cast<uint8_t>(val & 0xFF)
    };
}


#define COL_TO_SDL( p_color ) \
    p_color.r, p_color.g, p_color.b, p_color.a