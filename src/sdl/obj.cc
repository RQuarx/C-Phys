#include <SDL3/SDL.h>
#include "sdl/obj.hh"

using sdl::Object;


Object::Object( const f_pair & /* p_pos */, const Color &p_color ) :
    m_color(p_color)
{}


Object::~Object( void )
{}