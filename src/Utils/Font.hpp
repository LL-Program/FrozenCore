#pragma once

#include "../../raylib.h"
#include <string>

class FontManager
{
public:
    Font font;
    float typingSpeed;
    std::string text;
    std::string displayedText;
    float elapsedTime;
    size_t charIndex;
    bool isTyping;

    FontManager(const std::string &fontPath, int fontSize, float speed = 10.0f);
    ~FontManager();

    void StartTyping(const std::string &newText);
    void Update(float deltaTime);
    void Draw(Vector2 position, int fontSize, Color color);
};