#pragma once

#include "../../raylib.h"

extern Font pixelFontMain;

void InitFonts();
void DrawCustomFont(const char *text, Vector2 position, float size, Color color);