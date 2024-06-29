#include <chrono>
#include <memory>
#include <thread>

#include "SDL_timer.h"
#include "game.hpp"

std::unique_ptr<Game> game = nullptr;

int main() {
  game = std::make_unique<Game>();
  GameState gameState(60.0);
  std::chrono::steady_clock::time_point currentTime =
      std::chrono::steady_clock::now();
  uint32_t ticksAccumulator = 0u;
  uint32_t prevTicks = SDL_GetTicks();
  uint32_t currTicks = 0u;
  while (game->gameRunning()) {
    GameState newGameState = GameState::physics(gameState);
    gameState = newGameState;
    game->handleEvents();
    currTicks = SDL_GetTicks();
    ticksAccumulator += currTicks - prevTicks;
    game->update(ticksAccumulator);
    prevTicks = currTicks;
    bool frameskip = false;
    auto nextTime =
        currentTime + std::chrono::microseconds(
                          static_cast<long long int>(gameState.dt * 1000000.0));
    if (nextTime < std::chrono::steady_clock::now()) {
      frameskip = true;
    } else {
      std::this_thread::sleep_until(nextTime);
      frameskip = false;
    }
    currentTime = nextTime;
    if (!frameskip) {
      game->render();
    }
  }
  game->clear();

  return 0;
}