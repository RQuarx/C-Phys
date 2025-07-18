#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include "sdl/obj.hh"


class sdl
{
public:
    using event_func = std::function<SDL_AppResult(SDL_Window*, SDL_Renderer*)>;

    explicit sdl( const std::string &p_window_title );
    ~sdl( void );


    void add_obj( const std::shared_ptr<sdl_obj> &p_obj );


    template<typename T_Func, typename... T_Params>
    void add_event( const uint32_t p_type,
                    T_Func       &&p_func,
                    T_Params     &&...p_params )
    {
        event_func func =
        [p_func, p_params...](SDL_Window *p_w, SDL_Renderer *p_r){
            return p_func(p_w, p_r, p_params...);
        };

        m_event_funcs[p_type].push_back(func);
    }


    void add_event( const uint32_t p_type, event_func p_func );


    void run( void );

private:
    SDL_Window   *m_window;
    SDL_Renderer *m_render;

    std::unordered_map<uint32_t, std::vector<event_func>> m_event_funcs;
    std::vector<std::shared_ptr<sdl_obj>> m_objects;

    void init( const std::string &p_window_title );

    auto get_error( void ) const -> std::string;

    auto event_loop( SDL_Event &p_event ) -> SDL_AppResult;
};