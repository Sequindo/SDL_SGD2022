#include "game.hpp"

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

        // Initialize player
        this->playerEntity = std::make_unique<CowEntity>(
            GameConstants::playerFrameH, GameConstants::playerFrameW,
            GameConstants::playerEntityH, GameConstants::playerEntityW);
        playerEntity->placeTextureForEntity(&cowRestTexture);
        playerEntity->placeTextureForEntity(&cowMovingTexture);

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
        playerEntity->setCowMoving();
        break;
      case SDLK_RIGHT:
        playerEntity->setCowMoving();
        break;
      case SDLK_UP:
        playerEntity->setCowMoving();
        break;
      case SDLK_DOWN:
        playerEntity->setCowMoving();
        break;
      default:
        break;
      }
      break;
    case SDL_KEYUP:
      playerEntity->setCowResting();
      break;
    case SDL_QUIT:
      isGameRunning = false;
      break;
    default:
      break;
    }
}

void Game::update(uint32_t &animationTicks) {
  if (animationTicks < GameConstants::minTimeBetweenAnimationRefresh) {
    return;
  }
  playerEntity->updateCowSrcRect();
  animationTicks = 0u;
}

void Game::render() {
    SDL_RenderClear(renderer);
    // here we add stuff for rendering
    // TEST: render a player
    SDL_RenderCopy(renderer, playerEntity->getCowTexture()->getTexture(),
                   &playerEntity->getSrcRect(), &playerEntity->getDstRect());
    //end
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::gameRunning() {
    return isGameRunning;
}