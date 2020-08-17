#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"

class AssetManager;

class Game {

private:
  bool isRunning; 
  SDL_Window *window;

public:

  Game();
  ~Game();
  static SDL_Renderer *renderer;
  static AssetManager *assetManager;
  static SDL_Event event;
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


