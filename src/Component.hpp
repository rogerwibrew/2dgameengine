#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Entity;

class Component {
public:
  virtual ~Component() {}
  virtual void Initalise() {}
  virtual void Update(float deltaTime) {}
  virtual void Render() {}

  Entity *owner;

};


#endif // COMPONENT_HPP
