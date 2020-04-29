#define GSENGINE_EXPORT
#include "GUI/Controlls/Button.h"

Button::Button(int x, int y, int width, int heigth) :
    sprite(std::make_unique<CommonSprite>(glm::vec3(x, y, 0))),
    pressedSprite(std::make_unique<CommonSprite>(glm::vec3(x, y, 0)))
{
	sprite->SetSize(width, heigth);
	sprite->SetTexture("btn.png");
	sprite->SetShader("CommonSprite.vs", "CommonSprite.fs");

	pressedSprite->SetSize(width, heigth);
	pressedSprite->SetTexture("btnPressed.png");
	pressedSprite->SetShader("CommonSprite.vs", "CommonSprite.fs");
}

void Button::SetText(const std::wstring &text)
{
	this->text = text;
}

void Button::Press()
{
	isPressed = true;
	if(onPressedCb != nullptr) onPressedCb();
}

void Button::Release()
{
	isPressed = false;
}

void Button::Draw(const glm::mat4 &projection, const glm::mat4 &view)
{
	if (isPressed)
	{ 
		pressedSprite->Draw(projection, view);
	}	
	else
	{
		sprite->Draw(projection, view);
	}
}

void Button::SetCallback(OnBtnPressedCb cb)
{
	onPressedCb = cb;
}
