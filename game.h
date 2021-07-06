#ifndef GAME_H_
#define GAME_H_

#include "gamefield.h"

#include <SDL2/SDL.h>

class Game
{
private:
    SDL_Event m_event;
    SDL_Renderer *m_renderer;
    SDL_Window *m_window;

    bool m_isRunning;
    bool m_initialized;

    GameField *m_gamefield;

    void init();

public:
    void start();
    void stop();
};

#endif