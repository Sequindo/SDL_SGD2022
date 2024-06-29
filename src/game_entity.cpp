#include "game_entity.hpp"
#include "game_texture.hpp"

GameEntity::GameEntity(uint32_t singleFrameH, uint32_t singleFrameW,
                       uint32_t entityH, uint32_t entityW) {
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
  if (++currentFrame == entityTextures.at(textureIdx)->getFrameCount()) {
    currentFrame = START_FRAME_IDX;
  }
  srcRect.y = currentFrame * srcRect.h;
  srcRect.x = currentFrame * srcRect.w;
}

void CowEntity::setCowResting() { this->textureIndex = 0u; }

void CowEntity::setCowMoving() { this->textureIndex = 1u; }

GameTexture *CowEntity::getCowTexture() {
  return this->getTexture(textureIndex);
}

void CowEntity::updateCowSrcRect() { this->updateSrcRect(textureIndex); }
