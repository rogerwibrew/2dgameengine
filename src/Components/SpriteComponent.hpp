#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include "../TextureManager.hpp"
#include "../AssetManager.hpp"

class SpriteComponent : public Component {

private:
  TransformComponent* transform;
  SDL_Texture* texture;
  SDL_Rect srcRectangle;
  SDL_Rect dstRectangle;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
  
  SpriteComponent(const char* filePath) {
    SetTexture(filePath);
  }

  void SetTexture(std::string assetTextureID){
    texture = Game::assetManager->GetTexture(assetTextureID);
  }
 
  void Initalise() override {
    transform = owner->GetComponent<TransformComponent>();
    srcRectangle.x = 0;
    srcRectangle.y = 0;
    srcRectangle.w = transform->width;
    srcRectangle.h = transform->height;
  }

  void Update(float deltaTime) override {
    dstRectangle.x = (int)transform->position.x;
    dstRectangle.y = (int)transform->position.y;
    dstRectangle.w = transform->width * transform->scale;
    dstRectangle.h = transform->height * transform->scale;
};

  void Render() override {
    TextureManager::Draw(texture,  srcRectangle, dstRectangle, spriteFlip);
  }

std::string GetComponentType() override {
  std::string type = "SpriteComponent";
  return type;
} 
};
#endif   // SPRITECOMPONENT_HPP
