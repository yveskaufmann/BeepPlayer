#include "game.h"
#include "BeepPlayer.h"
#include "ExampleSongs.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define BLOCK_SIZE 20
#define BLOCKS_WITDH 8
#define BLOCKS_HEIGHT 15
#define SIDEBAR_WIDTH 60.0
#define SCREEN_WIDTH (BLOCK_SIZE * (BLOCKS_WITDH + 2)) + SIDEBAR_WIDTH
#define SCREEN_HEIGHT BLOCK_SIZE *(BLOCKS_HEIGHT + 1)
#define FONT_SIZE 12

Game::Game()
{
}

void Game::init()
{
    if (m_initialized)
    {
        return;
    }

    int windowFlags = 0;
    int renderFlags = SDL_RENDERER_ACCELERATED;

    m_window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        windowFlags);

    if (m_window == NULL)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    m_renderer = SDL_CreateRenderer(m_window, -1, renderFlags);
    if (m_renderer == NULL)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    BeepPlayer::start();

    if (TTF_Init() == -1)
    {
        SDL_Log("Failed to initialize SDL TTF: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    m_font = TTF_OpenFont("fonts/comic.ttf", FONT_SIZE);
    if (m_font == NULL)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    m_initialized = true;
}

void Game::start()
{
    this->init();
    this->initNewGame();
    BeepPlayer::playSong(BeepPlayer::ExampleSongs::TetrisGameBoyTheme);

    while (m_isRunning)
    {
        this->update();
        this->render();
    }
}

void Game::initNewGame()
{

    if (m_autoDropTimerID != 0)
    {
        SDL_RemoveTimer(m_autoDropTimerID);
        m_autoDropTimerID = 0;
    }

    m_gamefield = new GameField(BLOCKS_WITDH, BLOCKS_HEIGHT);
    m_isRunning = true;
    m_action = NONE;
    m_score = 0;
    m_rotationIdx = 0;
    m_blockPosition = Position(4, 0);
    m_block = (Block *)&Block::BLOCK_O;
}

Uint32 auto_drop_timer(Uint32 interval, void *param)
{

    SDL_UserEvent userEvent;
    userEvent.type = SDL_USEREVENT;
    userEvent.code = AUTO_DOWN;
    userEvent.data1 = NULL;
    userEvent.data2 = NULL;

    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user = userEvent;
    SDL_PushEvent(&event);

    return interval;
}

void Game::update()
{

    if (m_autoDropTimerID == 0)
    {
        m_autoDropTimerID = SDL_AddTimer(500, auto_drop_timer, NULL);
    }

    BeepPlayer::repeatCurrentFinishedSong();

    while (SDL_PollEvent(&m_event) != 0)
    {
        if (m_event.type == SDL_QUIT)
        {
            m_isRunning = false;
        }

        if (m_event.type == SDL_KEYUP)
        {
            m_action = NONE;
        }

        if (m_event.type == SDL_USEREVENT)
        {
            switch (m_event.user.code)
            {
            case AUTO_DOWN:
                m_action = AUTO_DOWN;
                break;
            }
        }

        if (m_event.type == SDL_KEYDOWN)
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_s:
            case SDLK_DOWN:
                m_action = DOWN;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                m_action = LEFT;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                m_action = RIGHT;
                break;
            case SDLK_r:
            case SDLK_SPACE:
                m_action = ROTATE;
                break;
            case SDLK_ESCAPE:
                m_action = RESET;
                this->initNewGame();
                return;

            default:
                break;
            }
        }
    }

    Position newPosition = m_blockPosition;
    int newRotationIdx = m_rotationIdx;
    switch (m_action)
    {
    case ROTATE:
        newRotationIdx = (m_rotationIdx + 1) % 4;
        break;
    case LEFT:
        newPosition.x--;
        break;
    case RIGHT:
        newPosition.x++;
        break;

    case DOWN:
        newPosition.y++;
        break;
    case AUTO_DOWN:
        newPosition.y++;
        break;
    default:
        break;
    }

    newPosition.x = std::min(std::max(newPosition.x, 0), BLOCKS_WITDH);
    newPosition.y = std::min(std::max(newPosition.y, 0), BLOCKS_HEIGHT);

    if (m_block != NULL)
    {
        bool canRender = true;
        auto oldPositions = m_block->getPositions(m_rotationIdx, m_blockPosition);
        for (auto pos : oldPositions)
        {
            this->m_gamefield->getField(pos.x, pos.y).unset();
        }

        auto newPositions = m_block->getPositions(newRotationIdx, newPosition);
        for (auto pos : newPositions)
        {
            if (pos.x < 0 || pos.x >= BLOCKS_WITDH || pos.y < 0 || pos.y >= BLOCKS_HEIGHT)
            {
                canRender = false;
                break;
            }

            if (!m_gamefield->isFree(pos.x, pos.y))
            {
                canRender = false;
                break;
            }
        }

        if (canRender)
        {

            for (auto pos : newPositions)
            {
                this->m_gamefield->getField(pos.x, pos.y).set(m_block->color);
            }

            m_blockPosition = newPosition;
            m_rotationIdx = newRotationIdx;
        }
        else if (m_action == AUTO_DOWN || m_action == DOWN)
        {
            this->lockBlocks();
        }
    }
    m_action = NONE;
}

void Game::lockBlocks()
{
    auto oldPositions = m_block->getPositions(m_rotationIdx, m_blockPosition);
    for (auto pos : oldPositions)
    {
        this->m_gamefield->getField(pos.x, pos.y).set(m_block->color);
    }

    int erasedRows = m_gamefield->eraseFullRows();
    if (erasedRows > 0)
    {
        m_score += erasedRows * 100;
    }

    m_blockPosition = Position(4, 0);

    switch (rand() % 7)
    {
    case 0:
        m_block = (Block *)&Block::BLOCK_I;
        break;
    case 1:
        m_block = (Block *)&Block::BLOCK_J;
        break;
    case 2:
        m_block = (Block *)&Block::BLOCK_L;
        break;
    case 3:
        m_block = (Block *)&Block::BLOCK_O;
        break;
    case 4:
        m_block = (Block *)&Block::BLOCK_S;
        break;
    case 5:
        m_block = (Block *)&Block::BLOCK_T;
        break;
    case 6:
        m_block = (Block *)&Block::BLOCK_Z;
        break;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0xCC, 0xCC, 0xCC, 0);
    SDL_RenderClear(m_renderer);

    int totalWidth = (BLOCKS_WITDH + 2) * BLOCK_SIZE;
    int totalHeight = (BLOCKS_HEIGHT + 1) * BLOCK_SIZE;

    int hOffset = 0;
    int yOffset = 0;

    for (int x = 0; x < BLOCKS_WITDH + 2; x++)
    {
        for (int y = 0; y < BLOCKS_HEIGHT + 1; y++)
        {

            SDL_Rect rect;
            rect.w = BLOCK_SIZE;
            rect.h = BLOCK_SIZE;
            rect.x = hOffset + x * rect.w;
            rect.y = yOffset + y * rect.h;

            if (y == BLOCKS_HEIGHT || x == 0 || x > BLOCKS_WITDH)
            {
                SDL_SetRenderDrawColor(m_renderer, 0x11, 0x11, 0x11, 0);
                SDL_RenderFillRect(m_renderer, &rect);
                SDL_SetRenderDrawColor(m_renderer, 0xee, 0xee, 0xee, 0);
                SDL_RenderDrawRect(m_renderer, &rect);
                continue;
            }

            auto field = m_gamefield->getField(x - 1, y);
            auto color = field.color;

            SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 0);
            SDL_RenderFillRect(m_renderer, &rect);

            SDL_SetRenderDrawColor(m_renderer, 0xee, 0xee, 0xee, 0);
            SDL_RenderDrawRect(m_renderer, &rect);
        }
    }

    char str[128];
    sprintf(str, "Score:\n%06d", m_score);

    SDL_Color textColor = {0xFF, 0xFF, 0xFF};
    SDL_Surface *pointsSurface = TTF_RenderText_Blended_Wrapped(m_font, str, textColor, SIDEBAR_WIDTH + 10);
    if (pointsSurface == NULL)
    {
        SDL_Log("Failed to render points: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture *pointsTexture = SDL_CreateTextureFromSurface(m_renderer, pointsSurface);
    if (pointsTexture == NULL)
    {
        SDL_Log("Failed to create points texture: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Rect pointsDest = {hOffset + totalWidth + 10, yOffset, pointsSurface->w, pointsSurface->h};
    SDL_RenderCopy(m_renderer, pointsTexture, NULL, &pointsDest);

    SDL_DestroyTexture(pointsTexture);
    SDL_FreeSurface(pointsSurface);

    SDL_RenderPresent(m_renderer);
}

void Game::stop()
{
    this->m_isRunning = false;
    if (m_initialized)
    {

        if (m_font != NULL)
        {
            TTF_CloseFont(m_font);
            m_font = NULL;
        }

        if (TTF_WasInit() == 1)
        {
            TTF_Quit();
        }

        if (m_autoDropTimerID != 0)
        {
            SDL_RemoveTimer(m_autoDropTimerID);
            m_autoDropTimerID = 0;
        }

        if (m_gamefield != NULL)
        {
            delete m_gamefield;
            m_gamefield = NULL;
        }

        if (m_window != NULL)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = NULL;
        }

        if (m_renderer != NULL)
        {
            SDL_DestroyWindow(m_window);
            m_window = NULL;
        }

        BeepPlayer::stop();
        m_initialized = false;
    }
}