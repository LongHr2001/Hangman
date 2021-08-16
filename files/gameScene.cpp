#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"game.h"
#include"SDL_init.h"
#include"word.h"

bool game::getQuit(){
    return quit;
}

bool game::getWin(){
    return won;
}

game::game(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight, int _difficulty, std::string _word){
    renderer = _renderer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;
    difficulty = _difficulty;
    word = _word;

    hintMax = word.length()/2;
    hintCount = hintMax;
    guessWord = std::string(word.length(), '-');

    std::string hintsLeft;
    if(hintCount == 1){
        hintsLeft = "You have 1 hint left";
    }
    else if(hintCount > 1){
        hintsLeft = "You have " + std::to_string(hintCount) + " hints left";
    }
    else{
        hintsLeft = "You have run out of hint...";
    }

    bg = loadTexture("bg.png", renderer);
    hangman = loadTexture("hangman.png", renderer);
    hintHelp = textToTexture("Press SPACE to use a hint!", "HangmanFont.ttf", color, 30, renderer);
    hint = textToTexture(hintsLeft, "HangmanFont.ttf", color, 30, renderer);

    std::string displayWord = string_toUpper(guessWord);
    guessed = textToTexture(displayWord, "HangmanFont.ttf", color, 30, renderer);

    wrongList = textToTexture("Wrong Letters:" + wrongLetter, "HangmanFont.ttf", color, 30, renderer);

    Update();
}

game::~game(){
    SDL_RenderClear(renderer);

    renderer = nullptr;

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(hangman);
    SDL_DestroyTexture(hint);
    SDL_DestroyTexture(guessed);
    SDL_DestroyTexture(wrongList);
}

void game::Input(){
    SDL_PollEvent(&input);

    if(input.type == SDL_QUIT){
        quit = true;
    }
    else if(input.type == SDL_KEYDOWN){
        if(input.key.keysym.sym == SDLK_SPACE){
            if(hintCount > 0){
                hintUpdate();
                hintCount -= 1;
            }

        }
        else if(input.key.keysym.sym >= SDLK_a && input.key.keysym.sym <= SDLK_z){
            guess = (char)(int)input.key.keysym.sym;
        }
    }
    else if(input.type == SDL_KEYUP){
        hintCount -= 0;
        guess = ' ';
    }
}

void game::Render(){
    static std::string wordNeedUpdate = guessWord;
    static int hintNeedUpdate = hintCount;
    static int wrongListSize = wrongLetter.length();

    renderTexture(bg, renderer, 0, 0);

    renderPartofTexture(hangman, renderer, 370, 50, 300*badGuessCount, 0, 300, 200);

    if(guessWord != wordNeedUpdate){
        SDL_DestroyTexture(guessed);

        std::string displayWord = string_toUpper(guessWord);
        guessed = textToTexture(displayWord, "HangmanFont.ttf", color, 30, renderer);
        wordNeedUpdate = guessWord;
    }

    int guessedWidth;
    SDL_QueryTexture(guessed, NULL, NULL, &guessedWidth, NULL);
    renderTexture(guessed, renderer, (windowWidth - guessedWidth)/2,280);

    if(hintCount > 0){
        int hintHelpWidth;
        SDL_QueryTexture(hintHelp, NULL, NULL, &hintHelpWidth, NULL);
        renderTexture(hintHelp, renderer, (windowWidth - hintHelpWidth)/2, 480);
    }

    if(hintCount != hintNeedUpdate){
        SDL_DestroyTexture(hint);

        std::string hintsLeft;
        if(hintCount == 1){
            hintsLeft = "You have 1 hint left";
        }
        else if(hintCount > 1){
            hintsLeft = "You have " + std::to_string(hintCount) + " hints left";
        }
        else{
            hintsLeft = "You have run out of hint...";
        }

        hint = textToTexture(hintsLeft, "HangmanFont.ttf", color, 30, renderer);
        hintNeedUpdate = hintCount;
    }

    int length = wrongLetter.length();
    if(length != wrongListSize){
        SDL_DestroyTexture(wrongList);

        wrongList = textToTexture("Wrong Letters:" + wrongLetter, "HangmanFont.ttf", color, 30, renderer);

        wrongListSize = length;
    }

    int wrongListWidth;
    SDL_QueryTexture(wrongList, NULL, NULL, &wrongListWidth, NULL);
    renderTexture(wrongList, renderer, (windowWidth - wrongListWidth)/2,320);


    int hintWidth;
    SDL_QueryTexture(hint, NULL, NULL, &hintWidth, NULL);
    renderTexture(hint, renderer, (windowWidth - hintWidth)/2,400);
}

void game::Update(){
    while(!quit && badGuessCount < maxBadGuess && guessWord != word){
        Input();

        static char inputGuard = ' ';

        if(guess != inputGuard ){
            if(contain(word, guess)){
                wordUpdate();
            }
            else if(guess != ' '){
                wrongLetterUpdate();
            }

            inputGuard = guess;
        }

        Render();

        SDL_RenderPresent(renderer);
    }

    if(guessWord == word){
        won = true;
    }
    else if(badGuessCount == maxBadGuess && guessWord != word){
        won = false;
    }
}
