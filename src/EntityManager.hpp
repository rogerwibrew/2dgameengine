#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Entity.hpp"
#include "Component.hpp"
#include "Constants.hpp"
#include <vector>
#include <iostream>

class EntityManager {
private:
  std::vector<Entity*> entities;
public:
  void ClearData();
  void Update(float deltaTime);
  void Render();
  bool HasNoEntities() const;
  unsigned int GetEntityCount() const;
  void ListAllEntities() const;
  std::vector<Entity*> GetEntities() const;
  std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
  Entity& AddEntity(std::string entityName, LayerType layer);
};

#endif // ENTITYMANAGER_HPP
