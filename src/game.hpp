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

    // Animation - related stuff
    inline const uint32_t maxTimeBetweenAnimationRefresh = 100u;
    inline const uint32_t minTimeBetweenAnimationRefresh = 1u;
    inline const uint32_t animationFreqStep = 16u;

    // Physics - related stuff
    inline const uint32_t playerAcceleration = 2u;
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
};

enum class AccelerationVec {
  HORIZONTAL_INC = 0,
  HORIZONTAL_DEC,
  VERTICAL_INC,
  VERTICAL_DEC,
  NONE
};

class PhysicStateAndMetadata {
  AccelerationVec accVec = AccelerationVec::NONE;
  uint32_t prevTicks;
  uint32_t dtTicks;

  uint32_t animationSpeed = 40u; // min ticks between updating player sprite
  uint32_t verticalSpeed = 0u;
  uint32_t horizontalSpeed = 0u;

public:
  PhysicStateAndMetadata() = default;
  void iterationIvoke();
  inline void setAccVec(AccelerationVec other) { this->accVec = other; }
  void handleAcceleration();
  inline uint32_t getAnimationSpeed() { return this->animationSpeed; }
  inline bool isPlayerMoving() { return !(verticalSpeed || horizontalSpeed); }
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
  PhysicStateAndMetadata physicState{};
  bool isGameRunning = true;
  std::unique_ptr<CowEntity> playerEntity = nullptr;

  // SDL stuff
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  GameTexture cowRestTexture{};
  GameTexture cowMovingTexture{};
};

#endif