#ifndef game_hpp
#define game_hpp

#define COW_MOVING_FRAME_ROWS 4
#define COW_MOVING_FRAME_COLS 4

#define COW_RESTING_FRAME_ROWS 4
#define COW_RESTING_FRAME_COLS 3

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
    inline const uint32_t width = 1366;
    inline const uint32_t height = 768;
    inline const uint32_t playerFrameH = 512;
    inline const uint32_t playerFrameW = 720;
    inline const uint32_t playerEntityH = 128;
    inline const uint32_t playerEntityW = 180;

    inline const uint32_t minTimeBetweenAnimationRefresh = 50u;
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
    void update(uint32_t &animationTicks);
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