#pragma once
#include <vector>
#include <SDL3/SDL_pixels.h>

struct SDL_Renderer;
struct SDL_FPoint;

using f_pair = std::pair<float, float>;


class sdl_obj
{
public:
    sdl_obj( void ) = default;
    sdl_obj( const f_pair &p_pos, const SDL_FColor &p_color );


    void draw( SDL_Renderer *p_render );

protected:
    std::vector<SDL_FPoint> m_points;
    SDL_FColor              m_color;
};