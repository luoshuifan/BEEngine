#pragma once
#include "BEPch.h"
#include <type_traits>


BE_BEGIN
template<typename... Args>
concept has_print = requires(Args... args)
{
	(std::cout << ... << args);
};

template<typename T>
concept has_multiplication = requires()
{
	T();
	T()* T();
};

BE_END