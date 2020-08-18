#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "../../lib/glm/glm.hpp"
#include "../AssetManager.hpp"
#include "../Component.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>
class TileComponent : public Component
{
public:
  SDL_Texture *texture;
  SDL_Rect srcRectangle;
  SDL_Rect dstRectangle;
  glm::vec2 position;

  TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize,
                int tileScale, std::string assetTextureId)
  {
    texture = Game::assetManager->GetTexture(assetTextureId);
    srcRectangle.x = sourceRectX;
    srcRectangle.y = sourceRectY;
    srcRectangle.w = tileSize;
    srcRectangle.h = tileSize;
    dstRectangle.x = x;
    dstRectangle.y = y;
    dstRectangle.w = tileSize * tileScale;
    dstRectangle.h = tileSize * tileScale;
    position.x = x;
    position.y = y;
  }
  ~TileComponent() { SDL_DestroyTexture(texture); }
  void Update(float deltaTime) override {
    dstRectangle.x = position.x - Game::camera.x;
    dstRectangle.y = position.y - Game::camera.y;
  }

  void Render() override
  {
    TextureManager::Draw(texture, srcRectangle, dstRectangle, SDL_FLIP_NONE);
  }
};

#endif // TILECOMPONENT_HPP