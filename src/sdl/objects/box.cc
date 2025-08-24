#include <SDL3/SDL.h>
#include "sdl/objects/box.hh"
#include "sdl/exception.hh"
#include "sdl/utils.hh"

using sdl::Box;


Box::Box( const f_pair &p_pos,
          const f_pair &p_size,
          const Color  &p_color,
          bool          p_fill ) :
    m_box({ .x = p_pos.first,
            .y = p_pos.second,
            .w = p_size.first,
            .h = p_size.second }),
    m_fill(p_fill)
{ m_color = p_color; }


Box::~Box( void )
{}


void
Box::draw( SDL_Renderer *p_render )
{
    SDL_SetRenderDrawColor(p_render, m_color.r, m_color.g,
                                     m_color.b, m_color.a);
    if (m_fill) {
        if (!SDL_RenderFillRect(p_render, &m_box))
            throw sdl::Exception("Failed to draw-fill a rectangle: {}",
                                  get_error());
    } else {
        if (!SDL_RenderRect(p_render, &m_box))
            throw sdl::Exception("Failed to draw a rectangle: {}", get_error());
    }
}


auto
Box::get_rect( void ) -> const SDL_FRect &
{ return m_box; }