#include "include/GameMap.h"
#include <cmath>
#include <cstdio>
#include <climits>
#include <ctime>
#include <noise/noise.h>
#include <SDL/SDL.h>

using namespace noise;

module::Perlin myPerlin;

struct pixel {
    uint8_t r, g, b, alpha;

    pixel(): r(0), g(0), b(0), alpha(0xFF) {}
};

pixel operator+(pixel p1, pixel p2) {
    pixel p;
    p.r = p1.r + p2.r;
    p.g = p1.g + p2.g;
    p.b = p1.b + p2.b;
    p.alpha = p1.alpha + p2.alpha;
    return p;
}


/*
 * x <= 1    ----> 0
 * x <= 10   ----> 1
 * x <= 100  ----> 2
 * ...
 * x <= 10E10  --> 10
*/
int logScale(int x) {
    if(x >= 10E11)
        return 20;
    else if(x >= 10E10)
        return 19;
    else if(x >= 10E9)
        return 18;
    else if(x >= 10E8)
        return 17;
    else if(x >= 10E7)
        return 16;
    else if(x >= 10E6)
        return 15;
    else if(x >= 10E5)
        return 14;
    else if(x >= 10E4)
        return 13;
    else if(x >= 10E3)
        return 12;
    else if(x >= 5)
        return 11;
    return 0;
}

pixel colorMap[21];
void genColorMap() {
    for(int i = 1; i < 11; i++) {
        colorMap[i].r = i * 20 + 20;
        colorMap[i].g = i * 10 + 20;
    }
    for(int i = 11; i < 21; i++){
        colorMap[i].b = (i - 10) * 20 + 10;
    }
}


void generateGameMap(int x, int y, int w, int h, GameTile& t) {
    double x1 = ((float)x / (float)w) * 2.0f;
    double y1 = ((float)y / (float)h) * 2.0f;
    t.height  = (int)(round(fabs(myPerlin.GetValue(x1, y1, 0) + 1)
            * 5.0f)) % 10 + 1;
}

inline void putpx(SDL_Surface* scr, int x, int y, pixel& p) {
    Uint32* p_screen = (Uint32*)scr->pixels;
    p_screen += y * scr->w + x;
    *p_screen = SDL_MapRGBA(scr->format, p.r, p.g, p.b, p.alpha);
}

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -100;
    }
    srand(time(0));
    genColorMap();
    SDL_Surface* window = SDL_SetVideoMode(600, 400, 32,
            SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Event event;

    GameMap world(600, 400);
    world.generateRandom(generateGameMap);
    for(int i = 0; i < 4000; i++) {
        //printf("frame %d\n", i);
        world.tick();
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                goto end;
            }
        }
        SDL_LockSurface(window);
        for(int x = 0; x < 600; x++) {
            for(int y = 0; y < 400; y++) {
                const GameTile& t = world(x, y);
                pixel p = colorMap[t.height] + colorMap[logScale(t.water)];
                putpx(window, x, y, p);
            }
        }
        SDL_UnlockSurface(window);
        SDL_Flip(window);
    }
end:
    SDL_Quit();
    return 0;
}
