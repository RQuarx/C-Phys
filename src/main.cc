#include <cstdint>
#include "sdl/objects/box.hh"
#include "sdl/sdl.hh"


auto
main( int32_t argc, char **argv ) -> int32_t
{
    sdl sdl("C+Physc");

    sdl.add_event(SDL_EVENT_QUIT,
    [](SDL_Window *p_w, SDL_Renderer *p_r){
        return SDL_APP_SUCCESS;
    });

    auto box = std::make_shared<sdl_box>(f_pair( 5, 5 ),
                                         f_pair( 100, 100 ),
                                         SDL_FColor( 1, 1, 1, 1 ),
                                         true);

    sdl.add_obj(box);

    sdl.run();

    return 0;
}