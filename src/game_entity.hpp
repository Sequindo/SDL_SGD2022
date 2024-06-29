#ifndef game_entity_hpp
#define game_entity_hpp

#include <vector>

#include "SDL_rect.h"

#define START_FRAME_IDX 0u

struct SDL_Rect;
typedef struct SDL_Rect SDL_Rect;

class GameTexture;

class GameEntity {
  friend class CowEntity;
  SDL_Rect srcRect{};
  SDL_Rect dstRect{};
  std::vector<GameTexture *> entityTextures{};

  uint32_t currentRow = START_FRAME_IDX;
  uint32_t currentCol = START_FRAME_IDX;

public:
  GameEntity(uint32_t singleFrameH, uint32_t singleFrameW, uint32_t entityH,
             uint32_t entityW);
  void placeTextureForEntity(GameTexture *gameTexturePtr);
  GameTexture *getTexture(uint32_t idx);
  const SDL_Rect &getSrcRect();
  const SDL_Rect &getDstRect();
  void updateSrcRect(uint32_t textureIdx);
  void updateDstRectCoords(int32_t dX, int32_t dY);
};

class CowEntity : public GameEntity {
  // Assume - first texture in vector for rest position, next one for moving
  uint32_t textureIndex = 0u;

public:
  CowEntity(uint32_t singleFrameH, uint32_t singleFrameW, uint32_t entityH,
            uint32_t entityW)
      : GameEntity(singleFrameH, singleFrameW, entityH, entityW) {}
  void setCowMoving();
  void setCowResting();
  GameTexture *getCowTexture();
  void updateCowSrcRect();
};

#endif