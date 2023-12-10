#define GSENGINE_EXPORT
#include "GUI/Screen.h"

#include "GUI/ScreenController.h"

Screen::Screen(int width, int height)
    : width(width), height(height), screenController(nullptr), view(1) {}

void Screen::SetScreenController(ScreenController* screenCtrl) {
    this->screenController = screenCtrl;
}
