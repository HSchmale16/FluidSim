#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <cstddef>
#include "Array2d.h"

struct GameTile {
    float height;
    float water;

    GameTile() {
        height = 1.0f;
        water = 0.0f;
    }
};

class GameMap {
public:
    GameMap(int w, int h);
    virtual ~GameMap();

    void generateRandom(void(*func)(int x, int y, GameTile&));
    void tick();
private:
    Array2d<GameTile> _map;
};

#endif // GAMEMAP_H
