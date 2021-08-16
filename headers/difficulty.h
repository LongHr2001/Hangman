#ifndef DIFFICULTY_H_INCLUDED
#define DIFFICULTY_H_INCLUDED

#include"SDL_init.h"

class diffScene{
    public:
        diffScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight);
        ~diffScene();

        bool getQuit();
        int getDifficulty();

    private:
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;

        SDL_Texture* bg;
        SDL_Texture* chooseDifficulty;
        SDL_Texture* easy;
        SDL_Texture* hard;
        SDL_Texture* pointer;

        int pointerY = 0;

        int difficulty = 0;
        int option = 1;

        SDL_Event input;

        bool quit = false;

        void Render();
        void Input();
        void Update();
};

#endif // DIFFICULTY_H_INCLUDED
