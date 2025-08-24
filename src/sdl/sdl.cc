#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "sdl/exception.hh"
#include "sdl/sdl.hh"
#include "logs.hh"

using sdl::Object;
using sdl::Main;


Main::Main( const std::string &p_window_title )
{
    init(p_window_title);
}


Main::~Main( void )
{
    LOG_DBG("Destroying application");
    if (m_render != nullptr) SDL_DestroyRenderer(m_render);
    if (m_window != nullptr) SDL_DestroyWindow(m_window);
    TTF_Quit();
    SDL_Quit();
}


auto
Main::get_error( void ) const -> std::string
{ return SDL_GetError(); }


void
Main::add_obj( Object *p_obj )
{
    LOG_DBG("Adding object to parent window.");
    m_objects.push_back(p_obj);
    p_obj->get_events(m_event_funcs);
}


void
Main::add_event( const uint32_t p_type, event_func p_func )
{
    LOG_DBG("Adding an event of type {} to the queue.", p_type);
    m_event_funcs[p_type].push_back(p_func);
}


void
Main::init( const std::string &p_window_title )
{
    LOG_INF("Initializing application");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        throw sdl::Exception("Failed to initialize SDL: {}", get_error());

    if (!TTF_Init())
        throw sdl::Exception("Failed to initialize SDL_ttf: {}", get_error());

    if (!SDL_SetAppMetadata(APP_NAME, APP_VERSION, "org.kei.c-phys"))
        throw sdl::Exception("Failed to set application metadata: {}",
                              get_error());

    if (!SDL_CreateWindowAndRenderer(p_window_title.c_str(), 800, 500,
                                     SDL_WINDOW_RESIZABLE,
                                    &m_window, &m_render))
        throw sdl::Exception("Failed to create window and renderer: {}",
                              get_error());

    if (!SDL_SetRenderVSync(m_render, 1))
        throw sdl::Exception("Failed to set render vsync type to adaptive: {}",
                              get_error());

    LOG_DBG("Successfully initialized SDL");
}


auto
Main::run( void ) -> int32_t
{
    bool running  { true };
    AppReturn val { RETURN_CONTINUE };

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            AppReturn retval { event_loop(event) };

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
Main::event_loop( SDL_Event &p_event ) -> AppReturn
{
    auto funcs { m_event_funcs[p_event.type] };
    EventData data {
        .window = m_window,
        .render = m_render,
        .event  = &p_event
    };

    for (const auto &func : funcs) {
        AppReturn res { func(data) };

        if (res == RETURN_SKIP)    return RETURN_SKIP;
        if (res == RETURN_FAILURE) return RETURN_FAILURE;
        if (res == RETURN_SUCCESS) return RETURN_SUCCESS;
    }

    return RETURN_CONTINUE;
}