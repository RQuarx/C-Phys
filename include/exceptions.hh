#pragma once
#include <format>


class app_error : std::exception
{
public:
    template<typename... T_Args>
    app_error( std::string_view p_fmt, T_Args &&...p_args ) :
        _msg(std::vformat(p_fmt, std::make_format_args(p_args...)))
    {}


    auto
    what( void ) const noexcept -> const char *
    { return _msg.c_str(); }

private:
    std::string _msg;
};


class sdl_error : public app_error
{ public: using app_error::app_error; };