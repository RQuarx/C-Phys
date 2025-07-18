#pragma once
#include <SDL3/SDL_pixels.h>
#include "sdl/obj.hh"


class sdl_box : public sdl_obj
{
public:
    sdl_box( const f_pair     &p_pos,
             const f_pair     &p_size,
             const SDL_FColor &p_color,
             bool              p_fill );

private:
};