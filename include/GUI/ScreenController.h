#ifndef GUI_SCREEN_CONTROLLER_HEADER
#define GUI_SCREEN_CONTROLLER_HEADER

#include <stack>
#include <memory>

#include "GUI/InputEventsListener.h"
#include "GUI/Screen.h"
#include "LibExports.h"

class ScreenController : public InputEventsListener
{
public:
	GSENGINE_API ScreenController();
	GSENGINE_API ~ScreenController() override;
	GSENGINE_API int AddScreen(std::unique_ptr<Screen> screen);
	GSENGINE_API void PreviousScreen();
	GSENGINE_API void DrawScreen(const std::shared_ptr<const Graphics> graphics);
	GSENGINE_API void UpdateScreen(float delta);
	GSENGINE_API void OnMouseButtonEvent(int btn, int action, int mods) override;
	GSENGINE_API void OnMouseCursorEvent(double x, double y) override;
	GSENGINE_API void OnMouseScrollEvent(double offsetX, double offsetY) override;
	GSENGINE_API void OnKeyboardEvent(int btn, int scanCode, int action, int mods) override;
private:
	std::stack<std::unique_ptr<Screen>> screens;
};

#endif //GUI_SCREEN_CONTROLLER_HEADER