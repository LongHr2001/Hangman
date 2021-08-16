#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include"SDL_init.h"

class menuScene{
public:
    menuScene(SDL_Renderer* renderer, int windowWidth);
    ~menuScene();
    void setWindowWidth(int windowWidth);

    bool getQuit();
    int getOption();



private:

    SDL_Renderer* renderer;

    SDL_Texture* bg;
    SDL_Texture* logo;
    SDL_Texture* playButton;
    SDL_Texture* creditButton;
    SDL_Texture* quitButton;
    SDL_Texture* menuPointer;

    int windowWidth;
    int menuPointerY = 293;

    SDL_Event input;
    int option = 1;

    bool quit = false;
    bool done = false;

    void setRenderer(SDL_Renderer* _renderer);
    int Input();
    void Render();
    void Update();
};

#endif // MENU_H_INCLUDED
