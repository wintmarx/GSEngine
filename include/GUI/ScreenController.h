#ifndef GUI_SCREEN_CONTROLLER_HEADER
#define GUI_SCREEN_CONTROLLER_HEADER

#include <memory>
#include <stack>

#include "GUI/InputEventsListener.h"
#include "LibExports.h"

class Screen;
class Graphics;

class ScreenController : public InputEventsListener {
public:
    GSENGINE_API ScreenController() = default;
    GSENGINE_API ~ScreenController() = default;
    GSENGINE_API int AddScreen(std::unique_ptr<Screen> screen);
    GSENGINE_API void PreviousScreen();
    GSENGINE_API void DrawScreen(const Graphics& graphics);
    GSENGINE_API void UpdateScreen(float delta);
    GSENGINE_API void OnMouseButtonEvent(int btn, int action, int mods) override;
    GSENGINE_API void OnMouseCursorEvent(float x, float y) override;
    GSENGINE_API void OnMouseScrollEvent(float offsetX, float offsetY) override;
    GSENGINE_API void OnKeyboardEvent(int btn, int scanCode, int action, int mods) override;

private:
    std::stack<std::unique_ptr<Screen>> screens;
};

#endif  // GUI_SCREEN_CONTROLLER_HEADER