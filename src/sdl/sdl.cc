#include <SDL3/SDL_init.h>

#include "exceptions.hh"
#include "sdl/sdl.hh"
#include "logs.hh"


sdl::sdl( const std::string &p_window_title )
{
    init(p_window_title);
}


sdl::~sdl( void )
{
    LOG_DBG("Destroying application");
    if (m_render != nullptr) SDL_DestroyRenderer(m_render);
    if (m_window != nullptr) SDL_DestroyWindow(m_window);
    SDL_Quit();
}


auto
sdl::get_error( void ) const -> std::string
{ return SDL_GetError(); }


void
sdl::add_obj( const std::shared_ptr<sdl_obj> &p_obj )
{
    LOG_DBG("Adding object to parent window.");
    m_objects.push_back(p_obj);
}


void
sdl::add_event( const uint32_t p_type, event_func p_func )
{
    LOG_DBG("Adding an event of type {} to the queue.", p_type);
    m_event_funcs[p_type].push_back(p_func);
}


void
sdl::init( const std::string &p_window_title )
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

    if (!SDL_SetRenderVSync(m_render, SDL_RENDERER_VSYNC_ADAPTIVE))
        throw sdl_error("Failed to set render vsync type to adaptive: {}",
                         get_error());

    LOG_DBG("Successfully initialized SDL");
}


void
sdl::run( void )
{
    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            auto retval = event_loop(event);

            if (retval == SDL_APP_FAILURE)
                exit(1);

            if (retval == SDL_APP_SUCCESS)
                running = false;
        }

        SDL_SetRenderDrawColorFloat(m_render, 0, 0, 0, 1);
        SDL_RenderClear(m_render);

        for (const auto &objs : m_objects)
            objs->draw(m_render);

        SDL_RenderPresent(m_render);
    }
}


auto
sdl::event_loop( SDL_Event &p_event ) -> SDL_AppResult
{
    auto funcs = m_event_funcs[p_event.type];

    for (const auto &func : funcs) {
        SDL_AppResult res = func(m_window, m_render);

        if (res == SDL_APP_SUCCESS) return SDL_APP_SUCCESS;
        if (res == SDL_APP_FAILURE) return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}