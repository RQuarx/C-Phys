#include "sdl/objects/label.hh"

using sdl::Label;


Label::Label( const f_pair      &p_pos,
              const std::string &p_text,
              const Color       &p_color ) :
    m_text(p_text)
{
    m_color = p_color;
    // TTF_C
}