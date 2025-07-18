#include <SDL3/SDL.h>
#include "exceptions.hh"
#include "logs.hh"
#include "sdl/obj.hh"


sdl_obj::sdl_obj( const f_pair &p_pos, const SDL_FColor &p_color ) :
    m_color(p_color)
{}


void
sdl_obj::draw( SDL_Renderer *p_render )
{
    LOG_DBG("Draw");
    if (!SDL_RenderPoints(p_render, m_points.data(), m_points.size()))
        throw sdl_error("Failed to render {} points: {}.",
                         m_points.size(), SDL_GetError());
}