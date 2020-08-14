#include <iostream>
#include "./Game.hpp"
#include "./Constants.hpp"

int main(int argc, char *args[]){

  Game *game = new Game();

  game->Initalise(WINDOW_WIDTH, WINDOW_HEIGHT);
  
  while(game->IsRunning()){
    game->ProcessInput();
    game->Update();
    game->Render();
  }

  game->Destroy();
  
  return 0;
}
