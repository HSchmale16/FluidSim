#include "include/GameMap.h"
#include <cmath>
#include <noise/noise.h>
#include <cstdio>
#include <SDL/SDL.h>

using namespace noise;

module::Perlin myPerlin;

struct pixel{
    uint8_t r, g, b, alpha;
};

pixel colorMap[20];
void genColorMap(){
    for(int i = 1; i < 11; i++){
        colorMap[i].r = i * 20 + 20;
        colorMap[i].g = i * 10 + 20;
    }
}


void generateGameMap(int x, int y, int w, int h, GameTile& t){
    double x1 = ((float)x / (float)w) * 2.0f;
    double y1 = ((float)y / (float)h) * 2.0f;
    t.height  = (int)(round(fabs(myPerlin.GetValue(x1, y1, 0) + 1)
                      * 5.0f)) % 10 + 1;
}

inline void putpx(SDL_Surface* scr, int x, int y, pixel& p){
    Uint32* p_screen = (Uint32*)scr->pixels;
    p_screen += y * scr->w + x;
    *p_screen = SDL_MapRGBA(scr->format, p.r, p.g, p.b, p.alpha);
}

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return -100;
    }
    genColorMap();
    SDL_Surface* window = SDL_SetVideoMode(600, 400, 32,
                                           SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Event event;

    GameMap world(600, 400);
    world.generateRandom(generateGameMap);
    for(int i = 0; i < 4000; i++) {
        //printf("frame %d\n", i);
        world.tick();
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                goto end;
            }
        }
        for(int x = 0; x < 600; x++){
            for(int y = 0; y < 400; y++){
                const GameTile& t = world(x, y);
                putpx(window, x, y, colorMap[t.height]);
            }
        }
        SDL_LockSurface(window);
        SDL_UnlockSurface(window);
        SDL_Flip(window);
    }
end:
    SDL_Quit();
    return 0;
}
