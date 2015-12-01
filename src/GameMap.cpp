#include "GameMap.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <cstdio>

GameMap::GameMap(int w, int h)
    : _map(w, h) {
}

GameMap::~GameMap() {
}

void GameMap::generateRandom(void (*func)(int,int,int,int, GameTile&)) {
    int w = _map.getWidth(),
        h = _map.getHeight();
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            func(i, j, w, h, _map(i, j));
        }
    }
    for(int i = 0; i < 10; i++) {
        Emitter e;
        e._x = rand() % w;
        e._y = rand() % h;
        e._amount = rand() % 200 + 2;
        _emitters.push_back(e);
        printf("(%d, %d) - %d\n", e._x, e._y, e._amount);
    }
}

void GameMap::tick() {
    int w = _map.getWidth();
    int h = _map.getHeight();
    // do the emitters first
    for(auto it = _emitters.begin(); it != _emitters.end(); it++) {
        _map(it->_x, it->_y).water += it->_amount;
        // printf("%d\n", it->_amount);
    }
    // now level the fluids
    for(int x = 1; x < w - 1; x++) {
        for(int y = 1; y < h - 1; y++) {
            tickTile(x, y);
        }
    }
}

void GameMap::tickTile(int x, int y) {
    /*if(_map(x,y).water <= 1){
        return;
    }*/
    //printf("skip\n");
    int height = _map(x,y).height;
    for(int x0 = x - 1; x0 < x + 1; x0++) {
        for(int y0 = y + 1; y0 > y - 1; y0--) {
            if((x0 == x) || (y0 == y))
                continue;
            int tarh = _map(x0, y0).height;
            if(height < tarh) {
                float dw = round((tarh - height) * .2);
                _map(x, y).water += dw;
                _map(x0, y0).water -= dw;
            }else{
                float dw = round((height - tarh) * .1);
                _map(x, y).water -= dw;
                _map(x0, y0).water += dw;
            }
        }
    }
}

const GameTile& GameMap::operator()(int x, int y) {
    return _map(x, y);
}
