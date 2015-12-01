#include "include/GameMap.h"
#include <cmath>
#include <noise/noise.h>
#include <cstdio>

using namespace noise;

module::Perlin myPerlin;

void generateGameMap(int x, int y, int w, int h, GameTile& t){
    double x1 = (float)x / (float)w;
    double y1 = (float)y / (float)h;
    t.height = myPerlin.GetValue(x1, y1, 0);
    printf("%f\n", t.height);
}

int main() {
    GameMap world(400, 600);
    world.generateRandom(generateGameMap);
    for(int i = 0; i < 100; i++) {
        world.tick();
    }
    return 0;
}
