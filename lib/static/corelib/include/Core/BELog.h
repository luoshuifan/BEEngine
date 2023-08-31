#pragma once
#include "BE.h"
#include "Traits.h"

BE_BEGIN

template <typename... Args>
requires has_print<Args...>
void BEPrint(const Args&... args)
{
	(std::cout << ... << (std::cout << "[ " << args , " ] ")) << std::endl;
}

BE_END