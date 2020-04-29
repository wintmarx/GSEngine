#ifndef GUI_SLIDER_HEADER
#define GUI_SLIDER_HEADER

#include "glm/glm.hpp"
#include "Graphics/Graphics.h"
#include "LibExports.h"

typedef void (*SliderCb)(double value, void *cbData);

class Slider
{
public:
	GSENGINE_API Slider(float x, float y, float width, float height, const glm::vec4 &color);
	GSENGINE_API ~Slider();
	GSENGINE_API void OnMouseButtonEvent(int btn, int action, int mods);
	GSENGINE_API void OnMouseCursorEvent(float x, float y);
	GSENGINE_API void Draw(std::shared_ptr<const Graphics> graphics, const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetCallback(SliderCb cb, void *data);
	GSENGINE_API void SetRange(float mix, float max);
	GSENGINE_API void SetValue(float value);
	GSENGINE_API void SetStep(float step);
	GSENGINE_API float GetValue();

private:
	float value = 0.;
	int stepNum = 0;
	int stepsCount = 0;
	float step = 0.;
	float max = 0.;
	float min = 0.;
	glm::vec4 lineParams{ 0.f };
	glm::vec4 circleParams{ 0.f };
	glm::vec4 sliderParams{ 0.f };
	SliderCb cb = nullptr;
	void *cbData = nullptr;
	bool isPressed = false;
	glm::vec4 color{ 0.f };
	glm::vec2 mousePos{ 0.f };
};

#endif //GUI_SLIDER_HEADER