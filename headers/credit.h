#ifndef CREDIT_H_INCLUDED
#define CREDIT_H_INCLUDED

#include"SDL_init.h"

class creditScene{
    public:
        creditScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight);
        ~creditScene();

        bool getQuit();
        bool Back();

    private:
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;

        SDL_Texture* bg;
        SDL_Texture* logo;
        SDL_Texture* gameBy;
        SDL_Texture* fontName;
        SDL_Texture* escToExit;


        bool quit = false;
        bool toMenu = false;

        SDL_Event input;
        void Input();

        void Render();
        void Update();
};

#endif // CREDIT_H_INCLUDED
