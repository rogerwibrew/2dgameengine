#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include "Entity.hpp"
#include "Component.hpp"

class EntityManager {
private:
  std::vector<Entity*> entities;
public:
  void ClearData();
  void Update(float deltaTime);
  void Render();
  bool HasNoEntities() const;
  Entity& AddEntity(std::string entityName);
  std::vector<Entity*> GetEntities() const;
  unsigned int GetEntityCount() const;
};

#endif // ENTITYMANAGER_HPP
