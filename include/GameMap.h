#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <cstddef>
#include <vector>
#include "Array2d.h"
#include "Emitter.h"

struct GameTile {
    int height;
    int water;

    GameTile() {
        height = 1.0f;
        water = 0.0f;
    }
};

class GameMap {
public:
    GameMap(int w, int h);
    virtual ~GameMap();

    void generateRandom(void(*func)(int x, int y, int w,
                                    int h, GameTile&));
    void tick();

    const GameTile& operator()(int x, int y);
private:
    Array2d<GameTile> _map;
    std::vector<Emitter> _emitters;
};

#endif // GAMEMAP_H
