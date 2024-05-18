#ifndef game_hpp
#define game_hpp

//forward declaration of SDL - related stuff
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;

struct SDL_Window;
typedef struct SDL_Window SDL_Window;

namespace GameConstants {
    inline const char* title {"Untitled Cow Gore Game"};
    inline const int width = 1366;
    inline const int height = 768; 
}

class Game {
public:
    Game();
    ~Game();
    void init(bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clear();
    bool gameRunning();
private:
    bool isGameRunning = true;

    //SDL stuff
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif