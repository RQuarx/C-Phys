#pragma once
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include "sdl/obj.hh"


namespace sdl
{
    class box : public object
    {
    public:
        box( void ) = default;

        box( const f_pair &p_pos,
             const f_pair &p_size,
             const color  &p_color,
             bool          p_fill );


        ~box( void );


        void draw( SDL_Renderer *p_render ) override;


        [[nodiscard]]
        auto get_rect( void ) -> const SDL_FRect &;

    protected:
        SDL_FRect m_box;

    private:
        bool m_fill;
    };
} /* namespace sdl */