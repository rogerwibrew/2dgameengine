#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP 

#include "Game.hpp"

class TextureManager {
  public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect srcRectangle, SDL_Rect dstRectangle, SDL_RendererFlip flip);
};

#endif // TEXTUREMANAGER_HPP
