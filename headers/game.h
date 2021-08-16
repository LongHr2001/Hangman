#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include"category.h"
#include "difficulty.h"
#include "gameScene.h"
#include"gameOver.h"


class gameScene{
    public:
        gameScene(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight);
        ~gameScene();

        bool getQuit();
        bool getDone();

    private:
        SDL_Renderer* renderer;

        catScene* categoryScene = nullptr;
        int category = 0;

        diffScene* difficultyScene = nullptr;
        int difficulty = 0;

        std::string fileName;

        std::string word;

        game* currentGame = nullptr;

        gameOver* over = nullptr;

        int windowWidth;
        int windowHeight;

        SDL_Event input;
        bool quit = false;
        bool win = false;
        bool done = false;

        void Update();
        void Input();

        void chooseWord();

};

#endif // GAME_H_INCLUDED
