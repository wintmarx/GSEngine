#ifndef GUI_WINDOW_HEADER
#define GUI_WINDOW_HEADER

#include <string>
#include <list>

#include "GLFW/glfw3.h"
#include "GUI/InputEventsListener.h"
#include "LibExports.h"

class Window
{
public:
	GSENGINE_API Window(const std::string &title, int width, int height);
	GSENGINE_API ~Window();
	GSENGINE_API double GetTime();
	GSENGINE_API bool IsWindowShouldClose();
	GSENGINE_API void PollEvents();
	GSENGINE_API void SwapBuffers();
	GSENGINE_API void AddInputEventsListener(InputEventsListener *listener);
	GSENGINE_API void RemoveInputEventsListener(InputEventsListener *listener);
private:
	void SubscribeToGLFWInputEvents();
	GLFWwindow *glfwWindow = nullptr;
	std::list<InputEventsListener*> inputEventsListeners;
};

#endif //GUI_WINDOW_HEADER