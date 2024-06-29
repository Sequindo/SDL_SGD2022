#include "game.hpp"
#include "game_misc.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

Game::Game() {
    this->init(false);
}

Game::~Game() {}

void Game::init(bool fullscreen) {
    int retVal = std::numeric_limits<int>::min();
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (0 == SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(GameConstants::title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GameConstants::width,
            GameConstants::height,
            SDL_WINDOW_SHOWN);
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        {
          // Player texture initialization
          SDL_Surface *tmpSurface =
              IMG_Load("../resources/spritesheets/"
                       "at-rest-facing-right-x720-y512-per-frame.png");
          cowRestTexture.setTexture(
              SDL_CreateTextureFromSurface(renderer, tmpSurface));
          cowRestTexture.setRowNum(COW_RESTING_FRAME_ROWS);
          cowRestTexture.setColNum(COW_RESTING_FRAME_COLS);
          SDL_FreeSurface(tmpSurface);
        }
        {
          SDL_Surface *tmpSurface = IMG_Load(
              "../resources/spritesheets/cowspritesheetx=720pxY=512px.png");
          cowMovingTexture.setTexture(
              SDL_CreateTextureFromSurface(renderer, tmpSurface));
          cowMovingTexture.setRowNum(COW_MOVING_FRAME_ROWS);
          cowMovingTexture.setColNum(COW_MOVING_FRAME_COLS);
          SDL_FreeSurface(tmpSurface);
        }
        {
          // Initialize slaughterhouse assets
          SDL_Surface *tmpSurface =
              IMG_Load("../resources/spritesheets/TRAPS.png");
          slaughterhouseAssetsTexture.setTexture(
              SDL_CreateTextureFromSurface(renderer, tmpSurface));
          slaughterhouseAssetsTexture.setRowNum(
              SLAUGHTERHOUSE_FLOOR_FRAME_ROWS);
          slaughterhouseAssetsTexture.setColNum(
              SLAUGHTERHOUSE_FLOOR_FRAME_COLS);
          SDL_FreeSurface(tmpSurface);
        }

        // Initialize player
        this->playerEntity = std::make_unique<CowEntity>(
            GameConstants::playerFrameH, GameConstants::playerFrameW,
            GameConstants::playerEntityH, GameConstants::playerEntityW);
        playerEntity->placeTextureForEntity(&cowRestTexture);
        playerEntity->placeTextureForEntity(&cowMovingTexture);

        // Initialize flooring
        this->slaughterhouseEntity = std::make_unique<GameEntity>(
            GameConstants::floorFrameSquare, GameConstants::floorFrameSquare,
            GameConstants::floorEntitySquare, GameConstants::floorEntitySquare);
        slaughterhouseEntity->placeTextureForEntity(
            &slaughterhouseAssetsTexture);
        slaughterhouseEntity->offsetSrcRect(107, 39);

        numFloorTilesColumn =
            static_cast<uint32_t>(GameConstants::height /
                                  GameConstants::floorEntitySquare) +
            1;
        numFloorTilesRow =
            static_cast<uint32_t>(GameConstants::width /
                                  GameConstants::floorEntitySquare) +
            1;
        // Append one extra floor tile to the row.
        numFloorTilesRow++;

        auto totalTilesNum = numFloorTilesRow * numFloorTilesColumn;
        this->floorRectangles.resize(totalTilesNum);
        resetFlooring();

    } else {
        std::cerr << SDL_GetError() << std::endl;
        isGameRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) { // Changes in acceleration
      case SDLK_LEFT:
        physicState.setAccVecHorizontal(AccelerationDirection::BACKWARD);
        break;
      case SDLK_RIGHT:
        physicState.setAccVecHorizontal(AccelerationDirection::FORWARD);
        break;
      case SDLK_UP:
        physicState.setAccVecVertical(AccelerationDirection::BACKWARD);
        break;
      case SDLK_DOWN:
        physicState.setAccVecVertical(AccelerationDirection::FORWARD);
        break;
      default:
        break;
      }
      break;
    case SDL_KEYUP:
      physicState.setAccVecHorizontal(AccelerationDirection::STALL);
      physicState.setAccVecVertical(AccelerationDirection::STALL);
      break;
    case SDL_QUIT:
      isGameRunning = false;
      break;
    default:
      break;
    }
}

void Game::resetFlooring() {
  uint32_t recIdx = 0u;
  for (uint32_t y = 0; y < numFloorTilesColumn; y++) {
    for (uint32_t x = 0; x < numFloorTilesRow; x++) {
      auto &rec = this->floorRectangles.at(recIdx++);
      rec.y = y * GameConstants::floorEntitySquare;
      rec.x = x * GameConstants::floorEntitySquare;
      rec.h = rec.w = GameConstants::floorEntitySquare;
    }
  }
}

// This moves not only the floortiles, but makes the whole map advance,
// including obstacles.
void Game::updateFlooring() {
  bool reset = false;

  // Sufficient to check the first tile in a vector, i.e. the top-left corner
  if (floorRectangles[0].x <= GameConstants::floorEntityLeftThreshold) {
    resetFlooring();
  } else {
    for (auto &rec : floorRectangles) {
      rec.x--;
    }
  }
}

void Game::update(uint32_t &animationTicks) {
  auto minTicksRequired =
      std::min<uint32_t>(this->physicState.getAnimationSpeed(),
                         GameConstants::floorAnimationTicks);
  if (animationTicks < minTicksRequired) {
    return;
  }
  physicState.isPlayerMoving() ? playerEntity->setCowMoving()
                               : playerEntity->setCowResting();
  if (animationTicks >= this->physicState.getAnimationSpeed()) {
    physicState.iterationIvoke();
    playerEntity->updateCowSrcRect();
    playerEntity->updateDstRectCoords(physicState.getHorizontalSpeed(),
                                      physicState.getVerticalSpeed());
  }
  if (animationTicks >= GameConstants::floorAnimationTicks) {
    this->updateFlooring();
  }
  if (animationTicks >= GameConstants::floorAnimationTicks &&
      animationTicks >= this->physicState.getAnimationSpeed()) {
    animationTicks = 0u;
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  // Render flooring
  for (const auto &dstRec : this->floorRectangles) {
    SDL_RenderCopy(
        renderer,
        slaughterhouseEntity->getTexture(SINGLE_TEXTURE_IDX)->getTexture(),
        &slaughterhouseEntity->getSrcRect(), &dstRec);
  }

  // Render a player
  SDL_RenderCopy(renderer, playerEntity->getCowTexture()->getTexture(),
                 &playerEntity->getSrcRect(), &playerEntity->getDstRect());
  // end
  SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::gameRunning() { return isGameRunning; }

void PhysicStateAndMetadata::iterationIvoke() {
  // Check dt (time) for calculations
  auto ticks = SDL_GetTicks();
  this->dtTicks = static_cast<double>((ticks - prevTicks) / 100.0);
  prevTicks = ticks;

  handleAcceleration();
}

void PhysicStateAndMetadata::handleAcceleration() {
  // Update animation speed
  // printf("Current animation set at %du\n", this->animationSpeed);
  if (accVecHorizontal != AccelerationDirection::STALL ||
      accVecVertical != AccelerationDirection::STALL) {
    if (animationSpeed <= GameConstants::animationFreqStep) {
      animationSpeed = GameConstants::minTimeBetweenAnimationRefresh;
    } else {
      this->animationSpeed =
          std::max<uint32_t>(GameConstants::minTimeBetweenAnimationRefresh,
                             animationSpeed - GameConstants::animationFreqStep);
    }
  } else {
    this->animationSpeed =
        std::min<uint32_t>(GameConstants::maxTimeBetweenAnimationRefresh,
                           animationSpeed + GameConstants::animationFreqStep);
  }

  // Update player speed and acceleration if needed
  switch (accVecHorizontal) {
  case AccelerationDirection::FORWARD:
    this->horizontalSpeed = this->horizontalSpeed +
                            GameConstants::playerAcceleration * this->dtTicks;
    break;
  case AccelerationDirection::BACKWARD:
    this->horizontalSpeed = this->horizontalSpeed -
                            GameConstants::playerAcceleration * this->dtTicks;
    break;
  default: // Slowing down if not accelerating (stall)
    if (this->horizontalSpeed > 0) {
      this->horizontalSpeed = std::max<int32_t>(
          0, this->horizontalSpeed -
                 GameConstants::playerAcceleration * this->dtTicks);
    } else {
      this->horizontalSpeed = std::min<int32_t>(
          0, this->horizontalSpeed +
                 GameConstants::playerAcceleration * this->dtTicks);
    }
    break;
  }
  switch (accVecVertical) {
  case AccelerationDirection::FORWARD:
    this->verticalSpeed =
        this->verticalSpeed + GameConstants::playerAcceleration * this->dtTicks;
    break;
  case AccelerationDirection::BACKWARD:
    this->verticalSpeed =
        this->verticalSpeed - GameConstants::playerAcceleration * this->dtTicks;
    break;
  default: // Slowing down if not accelerating (stall)
    if (this->verticalSpeed > 0) {
      this->verticalSpeed = std::max<int32_t>(
          0, this->verticalSpeed -
                 GameConstants::playerAcceleration * this->dtTicks);
    } else {
      this->verticalSpeed = std::min<int32_t>(
          0, this->verticalSpeed +
                 GameConstants::playerAcceleration * this->dtTicks);
    }
    break;
  }
}
