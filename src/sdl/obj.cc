#include <SDL3/SDL.h>
#include "exceptions.hh"
#include "sdl/obj.hh"
#include "logs.hh"

using sdl::object;


object::object( const f_pair & /* p_pos */, const color &p_color ) :
    m_color(p_color)
{}


object::~object( void )
{}


void
object::draw( SDL_Renderer *p_render )
{
    LOG_DBG("Draw");

    SDL_SetRenderDrawColor(p_render, m_color.r,
                                     m_color.g,
                                     m_color.b,
                                     m_color.a);
    if (!SDL_RenderPoints(p_render, m_points.data(), m_points.size()))
        throw sdl_error("Failed to render {} points: {}.",
                         m_points.size(), SDL_GetError());
}


void
object::get_events( events_container & /* p_events */ )
{}