#pragma once
#include <chrono>
#include "sdl/objects/box.hh"


namespace sdl
{
    class Button : public Box
    {
        using time = std::chrono::duration<long, std::ratio<1, 1000000000>>;
    public:
        Button( const f_pair &p_pos,
                const f_pair &p_size,
                const Color  &p_color,
                const Color  &p_on_hover,
                const Color  &p_on_clicked );

        ~Button( void );


        void draw( SDL_Renderer *p_render ) override;
        void get_events( events_container &p_events ) override;

    protected:
        Color m_hover_color;
        Color m_clicked_color;
        Color m_original_color;

        bool m_hovered;
        time m_start_press;

    private:

        /* Checks whether p_current_pos is within the rect's body. */
        auto is_in_bound( const f_pair &p_current_pos ) -> bool;
        auto cursor_event( EventData &p_data ) -> AppReturn;
    };
} /* namespace sdl */