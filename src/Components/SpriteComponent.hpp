#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include "../Animation.hpp"
#include "../TextureManager.hpp"
#include "../AssetManager.hpp"

class SpriteComponent : public Component {

private:
  TransformComponent* transform;
  SDL_Texture* texture;
  SDL_Rect srcRectangle;
  SDL_Rect dstRectangle;
  bool isAnimated;
  int numFrames;
  int animationSpeed;
  bool isFixed;
  std::map<std::string, Animation> animations;
  std::string currentAnimationName;
  unsigned int animationIndex = 0;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
  
  SpriteComponent(std::string assetTextureID) {
    isAnimated = false;
    isFixed = false;
    SetTexture(assetTextureID);
  }
  
  SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
    this->isAnimated = true;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
    this->isFixed = isFixed;

    if(hasDirections){
      Animation downAnimation = Animation(0,numFrames,animationSpeed);
      Animation rightanimation = Animation(1,numFrames,animationSpeed);
      Animation leftAnimation = Animation(2,numFrames,animationSpeed);
      Animation upAnimation = Animation(3,numFrames,animationSpeed);

      animations.emplace("downAnimation", downAnimation);
      animations.emplace("rightAnimation", rightanimation);
      animations.emplace("leftAnimation", leftAnimation);
      animations.emplace("upAnimation", upAnimation);

      animationIndex = 0;
      currentAnimationName = "downAnimation";

    }else {
      Animation singleAnimation = Animation(0, numFrames,  animationSpeed);   
      animations.emplace("SingleAnimation", singleAnimation);
      
      animationIndex = 0;
      this->currentAnimationName = std::string("SingleAnimation");
    }   
    Play(this->currentAnimationName);
    SetTexture(id);
  }

  void Play(std::string animationName){
    numFrames = animations[animationName].numFrames;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
//    currentAnimationName = animationName;
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
    if(isAnimated){
      srcRectangle.x = srcRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
    }
    srcRectangle.y = animationIndex * transform->height;
    dstRectangle.x = static_cast<int>(transform->position.x)- (isFixed ? 0 : Game::camera.x);
    dstRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0: Game::camera.y);
    dstRectangle.w = transform->width * transform->scale;
    dstRectangle.h = transform->height * transform->scale;
  }

  void Render() override {
    TextureManager::Draw(texture,  srcRectangle, dstRectangle, spriteFlip);
  }
};
#endif   // SPRITECOMPONENT_HPP
