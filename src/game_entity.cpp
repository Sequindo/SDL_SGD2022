#include "game_entity.hpp"
#include "game_texture.hpp"

GameEntity::GameEntity(uint32_t singleFrameH, uint32_t singleFrameW,
                       uint32_t entityH, uint32_t entityW) {
  this->entityTextures.reserve(2u);

  srcRect.h = singleFrameH;
  srcRect.w = singleFrameW;
  srcRect.x = 0u;
  srcRect.y = 0u;

  dstRect.h = entityH;
  dstRect.w = entityW;
}

void GameEntity::placeTextureForEntity(GameTexture *gameTexturePtr) {
  this->entityTextures.push_back(gameTexturePtr);
}

GameTexture *GameEntity::getTexture(uint32_t idx) {
  return this->entityTextures.at(idx);
}

const SDL_Rect &GameEntity::getSrcRect() { return srcRect; }

const SDL_Rect &GameEntity::getDstRect() { return dstRect; }

void GameEntity::updateSrcRect(uint32_t textureIdx) {
  auto tex = entityTextures.at(textureIdx);
  srcRect.x = currentRow * srcRect.w;
  srcRect.y = currentCol * srcRect.h;

  if (++currentRow == tex->getRowNum()) {
    currentRow = START_FRAME_IDX;
    ++currentCol;
    if (currentCol == tex->getColNum()) {
      currentCol = START_FRAME_IDX;
    }
  }
}

void CowEntity::setCowResting() {
  if (this->textureIndex == 0u) {
    return;
  }
  this->textureIndex = 0u;
  this->currentRow = 0u;
  this->currentCol = 0u;
}

void CowEntity::setCowMoving() {
  if (this->textureIndex == 1u) {
    return;
  }
  this->textureIndex = 1u;
  this->currentRow = 0u;
  this->currentCol = 0u;
}

GameTexture *CowEntity::getCowTexture() {
  return this->getTexture(textureIndex);
}

void CowEntity::updateCowSrcRect() { this->updateSrcRect(textureIndex); }
