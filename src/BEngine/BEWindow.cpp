#include "BEPch.h"
#include "BEWindow.h"



BE_BEGIN

BEWindow::BEWindow(uint32 W, uint32 H, const String& Name)
	:Width(W), Height(H)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Window = glfwCreateWindow(Width, Height, Name.c_str(), nullptr, nullptr);
}

BEWindow::~BEWindow()
{
	glfwDestroyWindow(Window);
}

BE_END