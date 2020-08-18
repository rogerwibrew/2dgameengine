#include <iostream>
#include "./Constants.hpp"
#include "./Game.hpp"
#include "./AssetManager.hpp"
#include "./Map.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Components/KeyboardControlComponent.hpp"
#include "../lib/glm/glm.hpp"
#include "Entity.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Map* map;

Game::Game() {
  isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initalise(int width, int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
    std::cerr << "Error initililising SDL." << std::endl;
    return;
  }
  window = SDL_CreateWindow(
      NULL,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      width,
      height,
      SDL_WINDOW_BORDERLESS);
  if(!window) {
    std::cerr << "Error creating SDL Window." << std::endl;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);
  if(!renderer) {
    std::cerr << "Error creating SDL Renderer." << std:: endl;
    return;
  }
  LoadLevel(0);
  manager.ListAllEntities(); 
  isRunning = true;
  return;
}

void Game::ProcessInput(){
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_ESCAPE)
        isRunning = false;
    default:
      break;
  }
}

void Game::Update(){
  int timeToWait = TARGET_FRAME_TIME - (SDL_GetTicks() - ticksLastFrame);
  if(timeToWait > 0 && timeToWait <= TARGET_FRAME_TIME) {
    SDL_Delay(timeToWait);
  }
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
  deltaTime = (deltaTime > 0.05f ? 0.05f : deltaTime);
  ticksLastFrame = SDL_GetTicks();
  manager.Update(deltaTime);
}


void Game::Render() {
  SDL_SetRenderDrawColor(renderer,21,21,21,255);
  SDL_RenderClear(renderer);
  if(manager.HasNoEntities()){
    return;
  }
  manager.Render();
  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::LoadLevel(int level){
  assetManager->AddTexture("tank-image", std::string("../assets/images/tank-big-right.png").c_str());
  assetManager->AddTexture("chopper-image", std::string("../assets/images/chopper-spritesheet.png").c_str());
  assetManager->AddTexture("jungle-tiletexture", std::string("../assets/tilemaps/jungle.png").c_str());

  map = new Map(std::string("jungle-tiletexture"), 1, 32);
  map->LoadMap(std::string("../assets/tilemaps/jungle.map"), 25, 20);

  Entity& tankEntity(manager.AddEntity("tank"));
  tankEntity.AddComponent<TransformComponent>(0,0,20,20,32,32,1);
  tankEntity.AddComponent<SpriteComponent>("tank-image");

  Entity& chopperEntity(manager.AddEntity("chopper"));
  chopperEntity.AddComponent<TransformComponent>(240, 106,0,0,32,32,1);
  chopperEntity.AddComponent<SpriteComponent>("chopper-image",2,90,true,false);
  chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
}
