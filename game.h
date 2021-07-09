#ifndef GAME_H_
#define GAME_H_

#include <cinttypes>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gamefield.h"
#include "block.h"

enum GameAction
{
    DOWN,
    AUTO_DOWN,
    LEFT,
    RIGHT,
    ROTATE,
    RESET,
    NONE,
};

enum GameState
{
    Game,
    Pause,
    RowCompleted,
    GameOver,
};

class Game
{
private:
    SDL_Event m_event;
    SDL_Renderer *m_renderer;
    SDL_Window *m_window;
    SDL_TimerID m_autoDropTimerID;
    TTF_Font *m_font;

    bool m_isRunning;
    bool m_initialized;
    uint32_t m_score;
    GameAction m_action;
    GameState m_state;
    GameField *m_gamefield;

    int m_rotationIdx;
    Position m_blockPosition;
    Block *m_block;

    void init();
    void initNewGame();
    void lockBlocks();
    bool canRenderBlock(Position &position, int rotationIdx);
    void createNewBlock();

public:
    Game();
    void start();
    void update();
    void render();
    void stop();
};

#endif