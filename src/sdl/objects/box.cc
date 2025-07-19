#include <SDL3/SDL.h>
#include "sdl/objects/box.hh"
#include "exceptions.hh"

using sdl::box;


box::box( const f_pair &p_pos,
          const f_pair &p_size,
          const color  &p_color,
          bool          p_fill ) :
    m_box({ .x = p_pos.first,
            .y = p_pos.second,
            .w = p_size.first,
            .h = p_size.second }),
    m_fill(p_fill)
{ m_color = p_color; }


box::~box( void )
{}


void
box::draw( SDL_Renderer *p_render )
{
    SDL_SetRenderDrawColor(p_render, m_color.r, m_color.g,
                                     m_color.b, m_color.a);
    if (m_fill) {
        if (!SDL_RenderFillRect(p_render, &m_box))
            throw sdl_error("Failed to draw-fill a rectangle: {}",
                             SDL_GetError());
    } else {
        if (!SDL_RenderRect(p_render, &m_box))
            throw sdl_error("Failed to draw a rectangle: {}", SDL_GetError());
    }
}


auto
box::get_rect( void ) -> const SDL_FRect &
{ return m_box; }