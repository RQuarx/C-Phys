#pragma once
#include <string>
#include "sdl/obj.hh"


namespace sdl
{
    class Label : public Object
    {
    public:
        Label( const f_pair      &p_pos,
               const std::string &p_text,
               const Color       &p_color );

        ~Label( void );
        void draw( SDL_Renderer *p_render ) override;

    protected:
        std::string m_text;

    private:
        
    };
} /* namespace sdl */