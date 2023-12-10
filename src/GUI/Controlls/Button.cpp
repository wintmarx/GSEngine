#define GSENGINE_EXPORT

#include "GUI/Controlls/Button.h"

#include "Graphics/Shapes/Sprites/CommonSprite.h"

Button::Button(int x, int y, int width, int height)
    : sprite(std::make_unique<CommonSprite>(glm::vec3(x, y, 0))),
      pressedSprite(std::make_unique<CommonSprite>(glm::vec3(x, y, 0))) {
    sprite->SetSize(width, height);
    sprite->SetTexture("btn.png");
    sprite->SetShader("CommonSprite.vs", "CommonSprite.fs");

    pressedSprite->SetSize(width, height);
    pressedSprite->SetTexture("btnPressed.png");
    pressedSprite->SetShader("CommonSprite.vs", "CommonSprite.fs");
}

void Button::SetText(const std::wstring& txt) { this->text = txt; }

void Button::Press() {
    isPressed = true;
    if (onPressedCb != nullptr) {
        onPressedCb(cbData);
    }
}

void Button::Release() { isPressed = false; }

void Button::Draw(const glm::mat4& projection, const glm::mat4& view) {
    if (isPressed) {
        pressedSprite->Draw(projection, view);
    } else {
        sprite->Draw(projection, view);
    }
}

void Button::SetCallback(OnBtnPressedCb cb, void* userData) {
    cbData = userData;
    onPressedCb = cb;
}
