#include "controller.h"

SDL_GameController *game_controller = NULL;

void controller_init()
{

    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == -1)
    {
        SDL_Log("Failed to SDL_INIT_GAMECONTROLLER: %s", SDL_GetError());
        return;
    }

    SDL_GameControllerEventState(SDL_ENABLE);

    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            game_controller = SDL_GameControllerOpen(i);
            if (game_controller != NULL)
            {
                SDL_Log("Found controller: %s", SDL_GameControllerName(game_controller));
                break;
            }

            SDL_Log("Failed to open controller %i: %s", i, SDL_GetError());
        }
    }

    if (game_controller == NULL)
    {
        SDL_Log("Found no controller fallback to keyboard");
    }
}

void controller_quit()
{

    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER))
    {
        SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    }

    if (game_controller == NULL)
    {
        SDL_GameControllerClose(game_controller);
        game_controller = NULL;
    }
}