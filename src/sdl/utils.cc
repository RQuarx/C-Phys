#include "sdl/exception.hh"
#include "sdl/utils.hh"


namespace sdl
{
    auto
    get_error( void ) -> std::string
    { return SDL_GetError(); }


    void
    set_cursor( SDL_Cursor *p_cursor )
    {
        if (!SDL_SetCursor(p_cursor))
            throw sdl::Exception("Failed to set cursor: {}", get_error());
    }


    void
    set_cursor( const SDL_SystemCursor &p_cursor )
    {
        SDL_Cursor *cursor { SDL_CreateSystemCursor(p_cursor) };
        if (cursor == nullptr)
            throw sdl::Exception("Failed to create system cursor: {}",
                                  get_error());
        set_cursor(cursor);
    }
}