#ifndef GUI_APPLICATION_HEADER
#define GUI_APPLICATION_HEADER

#include <string>

#include "GUI/Screen.h"
#include "GUI/ScreenController.h"
#include "GUI/Window.h"
#include "LibExports.h"

class Application {
public:
    GSENGINE_API Application(std::string title, int width, int height);
    GSENGINE_API ~Application();
    GSENGINE_API void Run(std::unique_ptr<Screen> mainScreen);

private:
    std::string title;
    int width = 800;
    int height = 600;
    std::unique_ptr<Window> wnd;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<ScreenController> screenCtrl;
};

#endif  // GUI_APPLICATION_HEADER