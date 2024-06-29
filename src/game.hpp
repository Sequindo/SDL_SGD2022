#ifndef game_hpp
#define game_hpp

//forward declaration of SDL - related stuff
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;
struct SDL_Window;
typedef struct SDL_Window SDL_Window;
struct SDL_Texture;
typedef struct SDL_Texture SDL_Texture;

namespace GameConstants {
    inline const char* title {"Untitled Cow Gore Game"};
    inline const int width = 1366;
    inline const int height = 768; 
}

class GameState {
public:
  double fps;
  double dt;

  GameState() = default;

  GameState(double fps) {
    this->fps = fps;
    dt = 1.0 / fps;
  };

  static GameState physics(const GameState &gs) {
    GameState game_state = gs;

    // logic for updating game state
    return game_state;
  }
};

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

    SDL_Texture* cowRestTexture = nullptr;
    SDL_Texture* cowMovingTexture = nullptr;
};

#endif