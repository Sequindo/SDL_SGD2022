#include <memory>
#include "game.hpp"

std::unique_ptr<Game> game = nullptr;

int main() {
  game = std::make_unique<Game>();

  while (game->gameRunning()) {
    game->handleEvents();
    game->update();
    game->render();
  }
  game->clear();

  return 0;
}