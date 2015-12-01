#include "GameMap.h"
#include <cassert>
#include <cmath>
#include <vector>

GameMap::GameMap(int w, int h)
    : _map(w, h) {
}

GameMap::~GameMap() {
}

void GameMap::generateRandom(void (*func)(int,int,int,int, GameTile&)) {
    for(int i = 0; i < _map.getWidth(); i++){
        for(int j = 0; j < _map.getHeight(); j++){
            func(i, j, _map.getWidth(), _map.getHeight(), _map(i, j));
        }
    }
    for(int i = 0; i < 10; i++){

    }
}

void GameMap::tick() {
}

const GameTile& GameMap::operator()(int x, int y){
    return _map(x, y);
}
