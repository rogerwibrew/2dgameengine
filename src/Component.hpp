#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Entity.hpp"

class Entity;

class Component {
public:
  virtual ~Component() {}
  virtual void Initalise() {}
  virtual void Update(float deltaTime) {}
  virtual void Render() {}
  virtual std::string GetComponentType() {}

  Entity *owner;

};


#endif // COMPONENT_HPP
