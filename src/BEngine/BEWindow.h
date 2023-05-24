#pragma once
#include "BE.h"
#include "GLFW/glfw3.h"

BE_BEGIN

class BEWindow
{
public:
	BEWindow(uint32 W, uint32 H, const String& Name);

	BEWindow() = default;

	~BEWindow();

	uint32 width;
	uint32 height;

	GLFWwindow* window;
};

BE_END