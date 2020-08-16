#include "AssetManager.hpp"
#include "./Components/TransformComponent.hpp"

AssetManager::AssetManager(EntityManager* manager):
  manager(manager)
{

}

void AssetManager::ClearData(){
  textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath){
  textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureID){
  return textures[textureID];
}


