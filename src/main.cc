#include <cstdint>
#include "sdl/objects/button.hh"
#include "sdl/sdl.hh"


auto
main( int32_t argc, char **argv ) -> int32_t
{
    sdl::main sdl("C+Physc");

    sdl.add_event(SDL_EVENT_QUIT,
    []( sdl::event_data & /* p_data */ ){
        return sdl::RETURN_SUCCESS;
    });

    sdl::button button ({ 5, 5 }, { 100, 100 },
                        { 48, 86,  113 },
                        { 66, 150, 250 },
                        { 15, 135, 250 });

    sdl.add_obj(&button);
    return sdl.run();
}