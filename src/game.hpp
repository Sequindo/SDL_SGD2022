#ifndef game_hpp
#define game_hpp

#define COW_MOVING_FRAME_NUM 16
#define COW_RESTING_FRAME_NUM 12

#include <memory>

#include "game_entity.hpp"
#include "game_texture.hpp"

//forward declaration of SDL - related stuff
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;
struct SDL_Window;
typedef struct SDL_Window SDL_Window;

class GameEntity;

namespace GameConstants {
    inline const char* title {"Untitled Cow Gore Game"};
    inline const int width = 1366;
    inline const int height = 768;

    inline const int playerFrameH = 512;
    inline const int playerFrameW = 720;
    inline const int playerEntityH = 128;
    inline const int playerEntityW = 180;
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
    std::unique_ptr<CowEntity> playerEntity = nullptr;

    //SDL stuff
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    GameTexture cowRestTexture{};
    GameTexture cowMovingTexture{};
};

#endif