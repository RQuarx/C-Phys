#pragma once
#include <source_location>
#include <format>
#include <string>


namespace sdl
{
    template<typename... T_Args>
    class Exception
    {
        struct ExceptionString
        {
            const char *fmt;
            std::source_location source;

            ExceptionString( const char                   *p_fmt,
                             const std::source_location   &p_source =
                                   std::source_location::current() ) :
                fmt(p_fmt), source(p_source)
            {}
        };

    public:
        Exception( ExceptionString p_fmt, T_Args &&...p_args ) :
            m_fmt(p_fmt),
            m_msg(std::vformat(m_fmt.fmt, std::make_format_args(p_args...)))
        {}


        auto
        what( void ) const noexcept -> const char *
        {
            std::string func { m_fmt.source.function_name() };
            func = func.substr(0, func.find('('));
            if (func.contains(' '))
                func = func.substr(func.find_first_of(' '));

            m_what = std::format("[{} in {}:{}]: {}",
                                  func,
                                  m_fmt.source.file_name(),
                                  m_fmt.source.line(),
                                  m_msg);
            return m_what.c_str();
        }

    private:
        ExceptionString m_fmt;
        std::string m_msg;
        std::string m_what;
    };
}