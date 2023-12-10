#ifndef GUI_INPUT_EVENTS_LISTENER_HEADER
#define GUI_INPUT_EVENTS_LISTENER_HEADER

#include "LibExports.h"

struct InputEventsListener {
    GSENGINE_API virtual void OnMouseButtonEvent(int btn, int action, int mods) = 0;
    GSENGINE_API virtual void OnMouseCursorEvent(float x, float y) = 0;
    GSENGINE_API virtual void OnMouseScrollEvent(float offsetX, float offsetY) = 0;
    GSENGINE_API virtual void OnKeyboardEvent(int btn, int scanCode, int action, int mods) = 0;
};

#endif  // GUI_INPUT_EVENTS_LISTENER_HEADER