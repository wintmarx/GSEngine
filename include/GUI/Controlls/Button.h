#ifndef GUI_BUTTON_HEADER
#define GUI_BUTTON_HEADER

#include <memory>
#include <string>

#include "LibExports.h"
#include "glm/glm.hpp"

typedef void (*OnBtnPressedCb)(void* userData);

class CommonSprite;

class Button {
public:
    enum class Type { Pictured, Colored };

    GSENGINE_API Button(int x, int y, int width, int height);
    GSENGINE_API ~Button() = default;
    GSENGINE_API void Press();
    GSENGINE_API void Release();
    GSENGINE_API void SetText(const std::wstring& text);
    GSENGINE_API void Draw(const glm::mat4& projection, const glm::mat4& view);
    GSENGINE_API void SetCallback(OnBtnPressedCb cb, void* userData = nullptr);

private:
    Type type = Type::Colored;
    std::wstring text;
    OnBtnPressedCb onPressedCb = nullptr;
    std::unique_ptr<CommonSprite> sprite;
    std::unique_ptr<CommonSprite> pressedSprite;
    bool isPressed = false;
    void* cbData = nullptr;
};

#endif  // GUI_BUTTON_HEADER