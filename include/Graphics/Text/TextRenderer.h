#pragma once
#include <string>
#include <vector>

class TextFont;

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();
    void DrawText(const std::string& text, float x, float y, int size);
    void DrawText(const std::string& text, float x, float y, int size, int rectColor);
    void DrawText(const std::string& text, float x, float y, int size, int outlineColor,
                  int outlineWidth);
    void SetFont(char* font);

private:
    std::vector<TextFont*>* fontsList;
};
