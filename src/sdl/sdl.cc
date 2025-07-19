#include <SDL3/SDL_init.h>

#include "exceptions.hh"
#include "sdl/sdl.hh"
#include "logs.hh"

using sdl::object;
using sdl::main;


main::main( const std::string &p_window_title )
{
    init(p_window_title);
}


main::~main( void )
{
    LOG_DBG("Destroying application");
    if (m_render != nullptr) SDL_DestroyRenderer(m_render);
    if (m_window != nullptr) SDL_DestroyWindow(m_window);
    SDL_Quit();
}


auto
main::get_error( void ) const -> std::string
{ return SDL_GetError(); }


void
main::add_obj( object *p_obj )
{
    LOG_DBG("Adding object to parent window.");
    m_objects.push_back(p_obj);
    p_obj->get_events(m_event_funcs);
}


void
main::add_event( const uint32_t p_type, event_func p_func )
{
    LOG_DBG("Adding an event of type {} to the queue.", p_type);
    m_event_funcs[p_type].push_back(p_func);
}


void
main::init( const std::string &p_window_title )
{
    LOG_INF("Initializing application");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        throw sdl_error("Failed to initialize SDL: {}", get_error());

    if (!SDL_SetAppMetadata(APP_NAME, APP_VERSION, "org.kei.c-phys"))
        throw sdl_error("Failed to set application metadata: {}", get_error());

    if (!SDL_CreateWindowAndRenderer(p_window_title.c_str(), 800, 500,
                                     SDL_WINDOW_RESIZABLE,
                                    &m_window, &m_render))
        throw sdl_error("Failed to create window and renderer: {}",
                         get_error());

    if (!SDL_SetRenderVSync(m_render, 1))
        throw sdl_error("Failed to set render vsync type to adaptive: {}",
                         get_error());

    LOG_DBG("Successfully initialized SDL");
}


auto
main::run( void ) -> int32_t
{
    bool running   = true;
    app_retval val = RETURN_CONTINUE;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            auto retval = event_loop(event);

            if (retval == RETURN_FAILURE) {
                val = RETURN_FAILURE;
                break;
            }

            if (retval == RETURN_SUCCESS) {
                val = RETURN_SUCCESS;
                break;
            }

            if (retval == RETURN_SKIP) {
                val = RETURN_SKIP;
                break;
            }

            val = RETURN_CONTINUE;
        }

        if (val == RETURN_SKIP) continue;
        if (val == RETURN_FAILURE || val == RETURN_SUCCESS)
            break;

        SDL_SetRenderDrawColorFloat(m_render, 0, 0, 0, 1);
        SDL_RenderClear(m_render);

        for (auto *obj : m_objects)
            obj->draw(m_render);

        SDL_RenderPresent(m_render);
    }

    if (val == RETURN_FAILURE) {
        return 1;
    } else { return 0; }
}


auto
main::event_loop( SDL_Event &p_event ) -> app_retval
{
    auto funcs = m_event_funcs[p_event.type];
    event_data data = {
        .window = m_window,
        .render = m_render,
        .event  = &p_event
    };

    for (const auto &func : funcs) {
        app_retval res = func(data);

        if (res == RETURN_SKIP)    return RETURN_SKIP;
        if (res == RETURN_FAILURE) return RETURN_FAILURE;
        if (res == RETURN_SUCCESS) return RETURN_SUCCESS;
    }

    return RETURN_CONTINUE;
}