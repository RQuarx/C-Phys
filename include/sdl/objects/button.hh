#pragma once
#include "sdl/objects/box.hh"


namespace sdl
{
    class button : public box
    {
        enum state
        {
            HOVERED,
            RELEASED,
            CLICKED
        };

    public:
        button( const f_pair &p_pos,
                const f_pair &p_size,
                const color  &p_color,
                const color  &p_on_hover,
                const color  &p_on_clicked );

        ~button( void );


        void draw( SDL_Renderer *p_render ) override;
        void get_events( events_container &p_events ) override;

    protected:
        state m_state;
        bool m_change_color;

        color m_hover_color;
        color m_clicked_color;
        color m_original_color;

    private:
        /* Checks whether p_current_pos is within the rect's body. */
        auto is_in_bound( const f_pair &p_current_pos ) -> bool;

        auto on_cursor_motion( event_data &p_data,
                               state &p_state ) -> app_retval;
    };
} /* namespace sdl */