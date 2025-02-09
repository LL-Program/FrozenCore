#include "CustomFont.hpp"

// QuinqueFive
Font pixelFontMain;

void InitFonts()
{
    pixelFontMain = LoadFont("resources/QuinqueFive.ttf");
}

void DrawCustomFont(const char* text, Vector2 position, float size, Color color) 
{
    DrawTextEx(pixelFontMain, text, position, size, 2, color);
}