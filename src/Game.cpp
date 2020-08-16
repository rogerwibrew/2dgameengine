#include <iostream>
#include "./Constants.hpp"
#include "./Game.hpp"
#include "./AssetManager.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

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

  ListEntities();

  
  isRunning = true;
  return;
}

void Game::ProcessInput(){
  SDL_Event event;
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


  std::string textureFilePath = "./assets/images/tank-big-right.png";
  assetManager->AddTexture("tank-image", textureFilePath.c_str());

  Entity& newEntity(manager.AddEntity("tank"));
  newEntity.AddComponent<TransformComponent>(0,0,20,20,32,32,1);
  newEntity.AddComponent<SpriteComponent>("tank-image");



  /* Entity& newEntityA(manager.AddEntity("projectileA")); */
  /* newEntityA.AddComponent<TransformComponent>(0,0,20,20,32,32,1); */


  /* Entity& newEntityB(manager.AddEntity("projectileB")); */
  /* newEntityB.AddComponent<TransformComponent>(0,0,30,30,32,32,1); */

  /* Entity& newEntityC(manager.AddEntity("projectileC")); */
  /* newEntityC.AddComponent<TransformComponent>(400,0,0,20,32,32,1); */

  /* Entity& newEntityD(manager.AddEntity("projectileD")); */
  /* newEntityD.AddComponent<TransformComponent>(800,0,-20,20,32,32,1); */

  /* Entity& newEntityE(manager.AddEntity("projectileE")); */
  /* newEntityE.AddComponent<TransformComponent>(400,600,0,-20,32,32,1); */
}
  
void Game::ListEntities() {
  std::vector<Entity*> entities = manager.GetEntities();
  
  for (auto& entity : entities){
    std::cout << "Entity Name: " << entity->name << std::endl;
    std::vector<Component*> components = entity->GetComponents();
    for(auto& component : components){
      std:: string type = component->GetComponentType();    
        std::cout << '\t' << "Component Type " << type << std::endl;
    }
  }
}
