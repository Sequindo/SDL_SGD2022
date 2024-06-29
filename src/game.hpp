#ifndef game_hpp
#define game_hpp

#define COW_MOVING_FRAME_ROWS 4
#define COW_MOVING_FRAME_COLS 4
#define COW_RESTING_FRAME_ROWS 4
#define COW_RESTING_FRAME_COLS 3
#define SLAUGHTERHOUSE_FLOOR_FRAME_ROWS 1
#define SLAUGHTERHOUSE_FLOOR_FRAME_COLS 1
#define SLAUGHTERHOUSE_BLADE_FRAME_ROWS 1
#define SLAUGHTERHOUSE_BLADE_FRAME_COLS 1
#define SINGLE_TEXTURE_IDX 0

#include <memory>

#include "game_entity.hpp"
#include "game_texture.hpp"

//forward declaration of SDL - related stuff
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;
struct SDL_Window;
typedef struct SDL_Window SDL_Window;

class GameEntity;

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

enum class AccelerationDirection { FORWARD, BACKWARD, STALL };

class PhysicStateAndMetadata {
  AccelerationDirection accVecHorizontal = AccelerationDirection::STALL;
  AccelerationDirection accVecVertical = AccelerationDirection::STALL;
  uint32_t prevTicks;
  double dtTicks;

  uint32_t animationSpeed = 40u; // min ticks between updating player sprite
  int32_t verticalSpeed = 0u;    // may be positive or negative
  int32_t horizontalSpeed = 0u;

public:
  PhysicStateAndMetadata() = default;
  void iterationIvoke();
  inline void setAccVecHorizontal(AccelerationDirection other) {
    this->accVecHorizontal = other;
  }
  inline void setAccVecVertical(AccelerationDirection other) {
    this->accVecVertical = other;
  }
  void handleAcceleration();
  inline uint32_t getAnimationSpeed() { return this->animationSpeed; }
  inline bool isPlayerMoving() { return (verticalSpeed || horizontalSpeed); }
  inline int32_t getHorizontalSpeed() { return this->horizontalSpeed; }
  inline int32_t getVerticalSpeed() { return this->verticalSpeed; }
};

class Game {
public:
    Game();
    ~Game();
    void init(bool fullscreen);
    void handleKeyboardInput();
    void handleEvents();
    void update(uint32_t &animationTicks);
    void render();
    void clear();
    bool gameRunning();

    void resetFlooring();
    void updateFlooring();
    std::vector<std::pair<uint32_t, uint32_t>> populateObstaclesCoords();
    void generateObstaclesPage();
    void checkAndRemoveDeadObstacles();
    bool areAnyObstaclesPresent();
    bool hasPlayerGotKilled();

  private:
    PhysicStateAndMetadata physicState{};
    bool isGameRunning = true;
    std::unique_ptr<CowEntity> playerEntity = nullptr;
    std::unique_ptr<GameEntity> slaughterhouseEntity = nullptr;
    std::unique_ptr<GameEntity> bladeEntity = nullptr;

    // Logic for obstacles
    std::vector<SDL_Rect> obstacles{};
    uint32_t obstaclesNum{0u};
    double currAngle{0u};

    // SDL stuff
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    GameTexture cowRestTexture{};
    GameTexture cowMovingTexture{};
    GameTexture slaughterhouseAssetsTexture{};
    std::vector<SDL_Rect> floorRectangles{};
    uint32_t numFloorTilesColumn{};
    uint32_t numFloorTilesRow{};
};

#endif