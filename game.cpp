#include "game.h"

#include <cstdlib>

#define BLOCK_SIZE 20
#define BLOCKS_WITDH 8
#define BLOCKS_HEIGHT 15
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void Game::init()
{
    if (m_initialized)
    {
        return;
    }

    m_gamefield = new GameField(BLOCKS_WITDH, BLOCKS_HEIGHT);

    int windowFlags = 0;
    int renderFlags = SDL_RENDERER_ACCELERATED;

    m_window = SDL_CreateWindow(
        "Game",
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

    m_initialized = true;
}

void Game::start()
{
    this->init();
    m_isRunning = true;
    while (m_isRunning)
    {
        while (SDL_PollEvent(&m_event) != 0)
        {
            if (m_event.type == SDL_QUIT)
            {
                m_isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(m_renderer, 0xCC, 0xCC, 0xCC, 0);
        SDL_RenderClear(m_renderer);

        int totalWidth = (BLOCKS_WITDH + 2) * BLOCK_SIZE;
        int totalHeight = (BLOCKS_HEIGHT + 1) * BLOCK_SIZE;

        int hOffset = SCREEN_WIDTH / 2 - totalWidth / 2;
        int yOffset = SCREEN_HEIGHT - totalHeight - BLOCK_SIZE * 2;

        uint8_t randomColors[][3] = {
            {0, 0, 0},
            {255, 0, 0},
            {255, 255, 0},
            {0, 255, 0},
            {0, 0, 255}};

        for (int x = 0; x < BLOCKS_WITDH + 2; x++)
        {
            for (int y = 0; y < BLOCKS_HEIGHT + 1; y++)
            {

                SDL_Rect rect;
                rect.w = BLOCK_SIZE;
                rect.h = BLOCK_SIZE;
                rect.x = hOffset + x * rect.w;
                rect.y = yOffset + y * rect.h;

                if (y == BLOCKS_HEIGHT || x == 0 || x == BLOCKS_WITDH + 1)
                {
                    SDL_SetRenderDrawColor(m_renderer, 0x11, 0x11, 0x11, 0);
                    SDL_RenderFillRect(m_renderer, &rect);
                    SDL_SetRenderDrawColor(m_renderer, 0xee, 0xee, 0xee, 0);
                    SDL_RenderDrawRect(m_renderer, &rect);
                }
                else
                {
                    uint8_t *color = randomColors[rand() % (sizeof(randomColors) / sizeof(Color))];

                    SDL_SetRenderDrawColor(m_renderer, color[0], color[1], color[2], 0);
                    SDL_RenderFillRect(m_renderer, &rect);

                    SDL_SetRenderDrawColor(m_renderer, 0xee, 0xee, 0xee, 0);
                    SDL_RenderDrawRect(m_renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(m_renderer);
    }
}

void Game::stop()
{
    this->m_isRunning = false;
    if (m_initialized)
    {
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
        m_initialized = false;
    }
}