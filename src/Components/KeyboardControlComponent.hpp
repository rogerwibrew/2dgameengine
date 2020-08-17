#ifndef KEYBOARDCONTROLCOMPONENT_HPP
#define KEYBOARDCONTROLCOMPONENT_HPP

#include "../Game.hpp"
#include "../EntityManager.hpp"
#include "./TransformComponent.hpp"
#include "./SpriteComponent.hpp"


class KeyboardControlComponent : public Component {
  public:

  std::string upKey;
  std::string downKey;
  std::string rightKey;
  std::string leftKey;
  std::string shootKey;
  TransformComponent *transform;
  SpriteComponent *sprite;

  KeyboardControlComponent() {}

  KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std:: string leftKey , std::string shootKey){
    this->upKey = GetSDLKeyString(upKey);
    this->rightKey = GetSDLKeyString(rightKey);
    this->downKey = GetSDLKeyString(downKey);
    this->leftKey = GetSDLKeyString(leftKey);
    this->shootKey = GetSDLKeyString(shootKey);
  }
  

  std::string GetSDLKeyString(std::string key){
            if (key.compare("up") == 0) return "1073741906";
            if (key.compare("down") == 0) return "1073741905";
            if (key.compare("left") == 0) return "1073741904";
            if (key.compare("right") == 0) return "1073741903";
            if (key.compare("space") == 0) return "32"; 
            return std::to_string(static_cast<int>(key[0]));
  }

  void Initalise() override {
    transform = owner->GetComponent<TransformComponent>();
    sprite = owner->GetComponent<SpriteComponent>();
  }

  void Update(float deltaTime) override {
    if(Game::event.type == SDL_KEYDOWN){
      std::string keyCode = std::to_string(Game::event.key.keysym.sym);

      if(keyCode.compare(upKey) == 0){
        transform->velocity.y = -40;
        transform->velocity.x = 0;
        sprite->Play("upAnimation");
      }
      if(keyCode.compare(rightKey) == 0){
        transform->velocity.y = 0;
        transform->velocity.x = 40;
        sprite->Play("rightAnimation");
      }
      if(keyCode.compare(downKey) == 0){
        transform->velocity.y = 40; 
        transform->velocity.x = 0;
        sprite->Play("downAnimation");

      }
      if(keyCode.compare(leftKey) == 0){
        transform->velocity.y = 0;
        transform->velocity.x = -40;
        sprite->Play("leftAnimation");

      }
      if(keyCode.compare(shootKey) == 0){

      }
    }
    if (Game::event.type == SDL_KEYUP){
      std::string keyCode = std::to_string(Game::event.key.keysym.sym);


      if(keyCode.compare(upKey) == 0){
        transform->velocity.y =0;
      }
      if(keyCode.compare(rightKey) == 0){
        transform->velocity.x = 0;
      }
      if(keyCode.compare(downKey) == 0){
        transform->velocity.y =0;
      } 
      if(keyCode.compare(leftKey) == 0){
        transform->velocity.x = 0;
      }
      if(keyCode.compare(shootKey) == 0){

      }
    }
  }
};



#endif  // KEYBOARDCONTROLCOMPONENT_HPP
