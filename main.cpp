#include "include/GameMap.h"
#include <cmath>

void generateGameMap(int x, int y, GameTile& t){

}

int main() {
    GameMap world(400, 600);
    world.generateRandom(generateGameMap);
    for(int i = 0; i < 100; i++) {
        world.tick();
    }
}
