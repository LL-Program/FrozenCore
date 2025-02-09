#pragma once

#include "../../raylib.h"
#include "../Entities/envItem.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

struct Tile
{
    int x, y;
    int spritesheet;
    int index;
    bool blocking;
};

std::vector<EnvItem> loadLevelData(const std::string &filename);