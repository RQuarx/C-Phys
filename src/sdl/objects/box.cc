#include <SDL3/SDL.h>
#include "sdl/objects/box.hh"
#include "logs.hh"


sdl_box::sdl_box( const f_pair     &p_pos,
                  const f_pair     &p_size,
                  const SDL_FColor &p_color,
                  bool              p_fill )
{
    m_color = p_color;

    float x_start = p_pos.first;
    float x_end   = p_pos.first + p_size.first;
    float y_start = p_pos.second;
    float y_end   = p_pos.second + p_size.second;

    /* top and bottom */
    for (float x = x_start; x < x_end; x++) {
        m_points.emplace_back(x, y_start);
        m_points.emplace_back(x, y_end);
    }

    /* left and right */
    for (float y = y_start; y < y_end; y++) {
        m_points.emplace_back(x_start, y);
        m_points.emplace_back(x_end, y);
    }

    if (p_fill) {
        for (float x = x_start + 1; x < x_end - 1; x++) {
            for (float y = y_start + 1; y < y_end - 1; y++) {
                m_points.emplace_back(x, y);
            }
        }
    }

    LOG_INF("Box has an area of {}px", m_points.size());
}