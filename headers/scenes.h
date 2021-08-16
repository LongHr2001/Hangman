#ifndef SCENES_H_INCLUDED
#define SCENES_H_INCLUDED

#include "menu.h"
#include "credit.h"
#include "game.h"

class scenesHandler{
    public:
        scenesHandler(SDL_Renderer* _renderer, int _WindowWidth, int _WindowHeight);
        ~scenesHandler();
        static bool instanceExisted();
        bool quit = false;

    private:
        enum Scenes{
            MENU_SCENE,
            GAME_SCENE,
            CREDIT_SCENE
        };

        Scenes currentScene = MENU_SCENE;

        SDL_Renderer* renderer;
        int WindowWidth;
        int WindowHeight;

        void Update();

        menuScene* menu = nullptr;
        creditScene* credit = nullptr;

        SDL_Event input;
        int Input();

        gameScene* game = nullptr;
};

#endif // SCENES_H_INCLUDED
