#ifndef GUI_SCREEN_HEADER
#define GUI_SCREEN_HEADER

#include "GUI/InputEventsListener.h"
#include "Graphics/Graphics.h"
#include "LibExports.h"

class ScreenController;

class Screen : public InputEventsListener {
public:
    GSENGINE_API Screen(int width, int height);
    GSENGINE_API ~Screen() = default;
    GSENGINE_API virtual void Update(float delta) = 0;
    GSENGINE_API virtual void Render(const Graphics& graphics) = 0;
    GSENGINE_API virtual void Initialize() = 0;
    GSENGINE_API void SetScreenController(ScreenController* screenController);

protected:
    int width{800};
    int height{600};
    ScreenController* screenController{};
    glm::mat4 projection{1};
    glm::mat4 view{1};
};

#endif  // GUI_SCREEN_HEADER