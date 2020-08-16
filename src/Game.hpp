#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "EntityManager.hpp"
#include "Component.hpp"
#include "Entity.hpp"

class AssetManager;

class Game {

private:
  bool isRunning; 
  SDL_Window *window;

  void ListEntities();

public:

  Game();
  ~Game();
  static SDL_Renderer *renderer;
  static AssetManager *assetManager;
  void LoadLevel(int level);
  void Initalise(int width, int height);
  void ProcessInput();
  void Update();
  void Render();
  void Destroy();
  bool IsRunning() const;
  int ticksLastFrame = 0;
};

#endif  // GAME_HPP


