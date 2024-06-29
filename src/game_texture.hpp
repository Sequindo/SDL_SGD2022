#ifndef game_texture_hpp
#define game_texture_hpp

struct SDL_Texture;
typedef struct SDL_Texture SDL_Texture;

class GameTexture {
  SDL_Texture *texture = nullptr;
  uint32_t rowNum = 0u;
  uint32_t colNum = 0u;

public:
  GameTexture() {}
  void setTexture(SDL_Texture *other) { texture = other; }
  void setRowNum(uint32_t other) { rowNum = other; }
  void setColNum(uint32_t other) { colNum = other; }
  SDL_Texture *getTexture() { return texture; }
  uint32_t getRowNum() { return rowNum; }
  uint32_t getColNum() { return colNum; }
};

#endif