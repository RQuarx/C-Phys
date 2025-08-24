#pragma once
#include <string>
#include <SDL3/SDL_mouse.h>


namespace sdl
{
    [[nodiscard]]
    auto get_error( void ) -> std::string;
    void set_cursor( SDL_Cursor *p_cursor );
    void set_cursor( const SDL_SystemCursor &p_cursor );
}