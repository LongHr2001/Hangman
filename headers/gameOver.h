#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

class gameOver{
    public:
        gameOver(SDL_Renderer* _renderer, int _windowWidth, int _windowHeight, bool _win, std::string& _word);
        ~gameOver();

        bool getQuit();
        int getReplay();

        static int winCount;
        static int loseCount;

    private:
        SDL_Renderer* renderer;
        int windowWidth;
        int windowHeight;
        bool win;
        std::string word;

        SDL_Texture* bg;
        SDL_Texture* man;
        SDL_Texture* answer;
        SDL_Texture* response;
        SDL_Texture* pointer;
        SDL_Texture* roundPlayed;
        SDL_Texture* roundWon;
        SDL_Texture* roundLost;
        SDL_Texture* replayPrompt;
        SDL_Texture* yes;
        SDL_Texture* no;

        int pointerY;

        int option = 1;

        int roundCount;

        SDL_Event input;

        bool quit = false;
        int replay = 0;

        void Render();
        void Input();
        void Update();
};

#endif // GAMEOVER_H_INCLUDED
