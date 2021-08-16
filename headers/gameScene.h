#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include<iostream>

#include"SDL_init.h"

class game{
    public:
        game(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight, int _difficulty, std::string _word);
        ~game();

        bool getQuit();
        bool getWin();

    private:
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;

        SDL_Texture* bg;
        SDL_Texture* hangman;
        SDL_Texture* guessed;
        SDL_Texture* hint;
        SDL_Texture* hintHelp;
        SDL_Texture* wrongList;

        SDL_Color color = {255, 255, 255, 255};

        int difficulty;

        std::string word;
        std::string guessWord;

        char guess;

        int badGuessCount = 0;
        const int maxBadGuess = 7;

        std::string wrongLetter;

        int hintMax = 0;
        int hintCount = 0;

        SDL_Event input;
        bool quit = false;
        bool won;

        void Input();
        void Render();
        void Update();

        void chooseWords();
        void wordUpdate();
        void hintUpdate();
        void wrongLetterUpdate();

};

#endif // GAMESCENE_H_INCLUDED
