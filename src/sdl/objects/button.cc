#include "sdl/objects/button.hh"
#include "exceptions.hh"
#include "logs.hh"

using sdl::button;


button::button( const f_pair &p_pos,
                const f_pair &p_size,
                const color  &p_color,
                const color  &p_on_hover,
                const color  &p_on_clicked ) :
    m_change_color(false),
    m_hover_color(p_on_hover),
    m_clicked_color(p_on_clicked),
    m_original_color(p_color)
{
    m_color = p_color;
    m_box = { .x = p_pos.first,
              .y = p_pos.second,
              .w = p_size.first,
              .h = p_size.second };
}


button::~button( void )
{}


void
button::draw( SDL_Renderer *p_render )
{
    LOG_DBG("Change color: {}", m_change_color);

    if (m_change_color) {
        switch (m_state) {
        case HOVERED:  m_color = m_hover_color;
        case CLICKED:  m_color = m_clicked_color;
        case RELEASED: m_color = m_original_color;
        }

        m_change_color = false;
    }

    LOG_DBG("Color: {}", m_color == m_original_color ? "Ori" : "Nah");

    SDL_SetRenderDrawColor(p_render, m_color.r, m_color.g,
                                     m_color.b, m_color.a);
    if (!SDL_RenderFillRect(p_render, &m_box))
        throw sdl_error("Failed to draw-fill a rectangle: {}",
                         SDL_GetError());
}


auto
button::is_in_bound( const f_pair &p_current_pos ) -> bool
{
    const std::array<float, 4> bound = {{
        m_box.x,           /* Min horizontal */
        m_box.x + m_box.w, /* Max horizontal */
        m_box.y,           /* Min vertical   */
        m_box.y + m_box.h, /* Max vertical   */
    }};

    if (p_current_pos.first  <= bound.at(0)) return false;
    if (p_current_pos.first  >= bound.at(1)) return false;
    if (p_current_pos.second <= bound.at(2)) return false;
    if (p_current_pos.second >= bound.at(3)) return false;
    return true;
}


auto
button::on_cursor_motion( event_data &p_data,
                          state      &p_state ) -> app_retval
{
    const f_pair current_pos = { p_data.event->motion.x,
                                 p_data.event->motion.y };

    if (is_in_bound(current_pos)) {
        m_change_color = true;
        p_state = HOVERED;

        return RETURN_CONTINUE;
    }

    /* Now we check if it is going from hover to normal. */
    if (m_hover_color == m_color) {
        m_change_color = true;
        p_state = RELEASED;

        return RETURN_CONTINUE;
    }

    return RETURN_CONTINUE;
}