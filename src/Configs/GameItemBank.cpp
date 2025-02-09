#include "GameItemBank.hpp"

// THERMAL BOMB
GameItem tr("Mechanical Shard", 0, &ItemMechanical, 40);
//SHARDS
GameItem aShard10("Antique Shards", 1, &shardsSheet, 10);
GameItem aShard20("Antique Shards", 2, &shardsSheet, 20);
GameItem aShard50("Antique Shards", 3, &shardsSheet, 50);
// HEART
GameItem heart("Heart", 4, &ItemHeart, 20);

GameItem* GetItemByID(int id)
{
    switch (id)
    {
    case 0:
        return &tr;
    case 1:
        return &aShard10;
    case 2:
        return &aShard20;
    case 3:
        return &aShard50;
    case 4:
        return &heart;
    case 5:
        return &tr;
    }

}