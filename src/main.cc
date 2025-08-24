#include <cstdint>
#include "sdl/objects/button.hh"
#include "sdl/objects/label.hh"
#include "sdl/sdl.hh"


auto
main( int32_t argc, char **argv ) -> int32_t
{
    sdl::Main sdl { "C+Physics" };

    sdl.add_event(SDL_EVENT_QUIT,
    []( sdl::EventData & /* p_data */ ){
        return sdl::RETURN_SUCCESS;
    });

    sdl::Button button { { 5, 5 }, { 100, 100 },
                         { 48, 86,  113 },
                         { 66, 150, 250 },
                         { 15, 135, 250 } };

    // sdl::Label label { { 15, 5 }, "Hello, World!", 0xFFFFFF_rgb };

    sdl.add_obj(&button);
    return sdl.run();
}