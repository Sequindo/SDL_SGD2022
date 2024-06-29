#ifndef game_texture_hpp
#define game_texture_hpp

struct SDL_Texture;
typedef struct SDL_Texture SDL_Texture;

class GameTexture {
  SDL_Texture *texture = nullptr;
  uint32_t frameCount = 0u;

public:
  GameTexture() {}
  void setTexture(SDL_Texture *other) { texture = other; }
  void setFrameCount(uint32_t other) { frameCount = other; }
  SDL_Texture *getTexture() { return texture; }
  uint32_t getFrameCount() { return frameCount; }
};

#endif