#ifndef GUI_SCREEN_HEADER
#define GUI_SCREEN_HEADER

#include <memory>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GUI/InputEventsListener.h"
#include "Graphics/Graphics.h"
#include "LibExports.h"

class ScreenController;

class Screen : public InputEventsListener
{
public:
	GSENGINE_API Screen(int width, int height);
	GSENGINE_API virtual ~Screen();
	GSENGINE_API virtual void Update(float delta) = 0;
	GSENGINE_API virtual void Render(const std::shared_ptr<const Graphics> graphics) = 0;
	GSENGINE_API virtual void Initialize() = 0;
	GSENGINE_API void SetScreenController(ScreenController *screenController);
	int width = 800;
	int height = 600;
protected:
	ScreenController *screenController;
	glm::mat4 projection;
	glm::mat4 view;
};

#endif //GUI_SCREEN_HEADER