#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <SDL2/SDL.h>
#include "../EntityManager.hpp"
#include "../../lib/glm/glm.hpp"
#include "../Game.hpp"

class TransformComponent : public Component {

public:
  glm::vec2 position;
  glm::vec2 velocity;
  int width;
  int height;
  int scale;

  TransformComponent(int posX, int posY, int velx, int velY, int w, int h, int s)
  {
    width = w;
    height = h;
    scale = s;
    position = glm::vec2(posX, posY);
    velocity = glm::vec2(velx,velY);
  }

  void Initalise() override {

  }

  void Update(float deltaTime) override {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
  }

  void Render() override {
  }
};
#endif // TRANSFORMCOMPONENT_HPP
