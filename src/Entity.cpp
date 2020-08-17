#include <iostream>
#include "Entity.hpp"

Entity::Entity(EntityManager& manager):
  manager{manager},
  isActive{true}
{}


Entity::Entity(EntityManager& manager, std::string name):
  manager{manager},
  isActive{true},
  name{name}
{}

void Entity::Update(float deltaTime){
  for (auto& component : components){
    component->Update(deltaTime);
  }
}

void Entity::Render(){
  for(auto& component : components){
    component->Render();
  }
}

void Entity::Destroy(){
  isActive = false;
}

bool Entity::IsActive() const {
  return isActive;
}

std::vector<Component*> Entity::GetComponents() const{
  return components; 
}

void Entity::ListAllComponents() const {
  for (auto& mapElement : componentTypeMap) {
    std::cout << "  Component<" << mapElement.first->name()
                                                            <<  ">" << std::endl;
  }
}
