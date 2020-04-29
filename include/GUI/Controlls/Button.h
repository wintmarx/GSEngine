#ifndef GUI_BUTTON_HEADER
#define GUI_BUTTON_HEADER

#include <string>

#include "Graphics/Shapes/Sprites/CommonSprite.h"
#include "glm/glm.hpp"
#include "LibExports.h"

enum class ButtonType
{
	Pictured,
	Colored
};

typedef void (*OnBtnPressedCb)();

class Button
{
public:
	GSENGINE_API Button(int x, int y, int width, int height);
	GSENGINE_API ~Button() = default;
	GSENGINE_API void Press();
	GSENGINE_API void Release();
	GSENGINE_API void SetText(const std::wstring &text);
	GSENGINE_API void Draw(const glm::mat4 &projection, const glm::mat4 &view);
	GSENGINE_API void SetCallback(OnBtnPressedCb cb);

private:
	ButtonType type = ButtonType::Colored;
	std::wstring text = L"";
	OnBtnPressedCb onPressedCb = nullptr;
	std::unique_ptr<CommonSprite> sprite;
	std::unique_ptr<CommonSprite> pressedSprite;
	bool isPressed = false;
};

#endif // GUI_BUTTON_HEADER