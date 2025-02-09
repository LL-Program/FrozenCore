#pragma once

#include <iostream>
#include <vector>
#include "player.hpp"
#include "../Utils/constants.hpp"
#include "../../raylib.h"

bool AddItemToInventory(std::vector<int> &inventory, int itemId);
void HandleInventoryScrolling(Player *player);
