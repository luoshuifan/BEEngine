#pragma once
#include "BE.h"

BE_BEGIN

template<typename... Args>
concept has_print = requires(Args... args)
{
	(std::cout << ... << args);
};

template <typename... Args>
requires has_print<Args...>
void BEPrint(const Args&... args)
{
	(std::cout << ... << (std::cout << "[ " << args , " ] ")) << std::endl;
}

BE_END