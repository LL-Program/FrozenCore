#include "Font.hpp"

FontManager::FontManager(const std::string &fontPath, int fontSize, float speed)
{
    font = LoadFontEx(fontPath.c_str(), fontSize, nullptr, 0);
    typingSpeed = speed;
    elapsedTime = 0.0f;
    charIndex = 0;
    isTyping = false;
}

FontManager::~FontManager()
{
    UnloadFont(font);
}

void FontManager::StartTyping(const std::string &newText)
{
    text = newText;
    displayedText = "";
    elapsedTime = 0.0f;
    charIndex = 0;
    isTyping = true;
}

void FontManager::Update(float deltaTime)
{
    if (isTyping)
    {
        elapsedTime += deltaTime;
        size_t newChars = static_cast<size_t>(elapsedTime * typingSpeed);
        if (newChars > charIndex)
        {
            charIndex = newChars;
            if (charIndex >= text.length())
            {
                charIndex = text.length();
                isTyping = false;
            }
            displayedText = text.substr(0, charIndex);
        }
    }
}

void FontManager::Draw(Vector2 position, int fontSize, Color color)
{
    DrawTextEx(font, displayedText.c_str(), position, fontSize, 1, color);
}
