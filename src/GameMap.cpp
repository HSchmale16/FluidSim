#include "GameMap.h"
#include <cassert>
#include <cmath>

GameMap::GameMap(int w, int h)
    : _map(w, h) {
}

GameMap::~GameMap() {
}

void GameMap::generateRandom(void (*func)(int x, int y, GameTile&)) {
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            func(i, j, _map(i, j));
        }
    }
}

void GameMap::tick() {
}
