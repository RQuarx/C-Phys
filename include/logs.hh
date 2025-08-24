#pragma once
#include <format>
#include <string>
#include <print>

#ifdef __DEBUG
    #define LOG_DBG( p_fmt, ... )                   \
        log("\033[1;36mDEBUG", __PRETTY_FUNCTION__, \
             p_fmt __VA_OPT__(,) __VA_ARGS__)
#else
    #define LOG_DBG( p_fmt, ... ) do {} while (false)
#endif

#define LOG_INF( p_fmt, ... ) \
    log("\033[1;32mINFO", __PRETTY_FUNCTION__, p_fmt __VA_OPT__(,) __VA_ARGS__)

template<typename... T_Args>
constexpr void log( const std::string &p_label,
                    const std::string &p_func,
                    std::string_view   p_fmt,
                    T_Args        &&...p_args )
{
    std::string msg { std::vformat(p_fmt,
                                   std::make_format_args(p_args...)) };
    std::string func { p_func.substr(0, p_func.find_first_of('(')) };
    if (func.contains(' '))
        func = p_func.substr(p_func.find_first_of(' '));

    if (func.front() == ' ')
        func.erase(0, 1);

    std::println("{:<13}\033[0;0m on {:<40}: {}", p_label, func, msg);
}