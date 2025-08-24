#pragma once
#include <string>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include "sdl/types.hh"
#include "sdl/obj.hh"


namespace sdl
{
    class Main
    {
    public:
        explicit Main( const std::string &p_window_title );
        ~Main( void );


        void add_obj( Object *p_obj );


        template<typename T_Func, typename... T_Params>
        void add_event( const uint32_t p_type,
                        T_Func       &&p_func,
                        T_Params     &&...p_params )
        {
            event_func func =
            [p_func, p_params...](EventData &p_data){
                return p_func(p_data, p_params...);
            };

            m_event_funcs[p_type].push_back(func);
        }


        void add_event( const uint32_t p_type, event_func p_func );


        auto run( void ) -> int32_t;

    private:
        SDL_Window   *m_window;
        SDL_Renderer *m_render;

        std::vector<Object *> m_objects;
        events_container       m_event_funcs;

        void init( const std::string &p_window_title );

        [[nodiscard]]
        auto get_error( void ) const -> std::string;

        [[nodiscard]]
        auto event_loop( SDL_Event &p_event ) -> AppReturn;
    };
} /* namespace sdl */