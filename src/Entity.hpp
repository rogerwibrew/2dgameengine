#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <string>
#include <map>

#include "Component.hpp"
#include "EntityManager.hpp"

class Component;
class EntityManager;

class Entity {

private:
  EntityManager& manager;
  bool isActive;
  std::vector<Component*> components;
  std::map<const std::type_info*, Component*> componentTypeMap;

public:
  std::string name;
  Entity(EntityManager& manager);
  Entity(EntityManager& manager, std::string name);
  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool IsActive() const;
  std::vector<Component*> GetComponents() const;

  template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args){
      T* newComponent(new T(std::forward<TArgs>(args)...));
      
      newComponent->owner = this;
      components.emplace_back(newComponent);
      componentTypeMap[&typeid(*newComponent)] = newComponent;
      newComponent->Initalise();
      return *newComponent;
    }

  template <typename T> 
    T* GetComponent() {
      return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }
};
#endif  // ENTITY_HPP
