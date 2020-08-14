#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>


#include "Constants.hpp"
#include "../lib/glm/glm.hpp"
#include "EntityManager.hpp"
#include "Component.hpp"
#include "Entity.hpp"

class Game {

private:
  bool isRunning; 
  int ticksLastFrame;
  void ListEntities();

  SDL_Window *window;

public:

  static SDL_Renderer *renderer;
  Game();
  ~Game();
  void LoadLevel(int level);
  void Initalise(int width, int height);
  void ProcessInput();
  void Update();
  void Render();
  void Destroy();
  bool IsRunning() const;
};

#endif  // GAME_HPP


