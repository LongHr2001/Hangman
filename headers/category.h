#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

#include"SDL_init.h"

class catScene{
    public:
        catScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight);
        ~catScene();

        bool getQuit();
        int getCategory();

    private:
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;

        SDL_Texture* bg;
        SDL_Texture* chooseCategory;
        SDL_Texture* animals;
        SDL_Texture* bodyparts;
        SDL_Texture* foods;
        SDL_Texture* jobs;
        SDL_Texture* objects;
        SDL_Texture* places;
        SDL_Texture* plants;
        SDL_Texture* random;
        SDL_Texture* pointer;

        int pointerY = 0;

        int category = 0;
        int option = 1;

        SDL_Event input;

        bool quit = false;

        void Render();
        void Input();
        void Update();
};


#endif // CATEGORY_H_INCLUDED
