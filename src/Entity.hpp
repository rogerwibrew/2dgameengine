#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include "EntityManager.hpp"
#include "Component.hpp"
#include "Constants.hpp"

class Component;
class EntityManager;

class Entity {

private:
  EntityManager& manager;
  bool isActive;
  std::vector<Component*> components;
  std::map<const std::type_info*, Component*> componentTypeMap;

public:
  Entity(EntityManager& manager);
  Entity(EntityManager& manager, std::string name, LayerType layer);
  std::string name;
  LayerType layer;
  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool IsActive() const;
  std::vector<Component*> GetComponents() const;
  void ListAllComponents() const;

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

  /* template <typename T> */
  /*   /1* bool HasComponent() const { *1/ */
    /*   const std::type_info* type = &typeid(T); */
    /*   std::map<const std::type_info*, Component*>::iterator it; */
    /*   it = componentTypeMap.find(type); */
    /*   if(it != componentTypeMap.end()) { */
    /*     return true; */
    /*   } */
    /*   return false; */
    /* } */
};

#endif  // ENTITY_HPP
