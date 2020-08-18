#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "../Component.hpp"
#include "../Game.hpp"
#include "../EntityManager.hpp"
#include "./TransformComponent.hpp"
#include <SDL2/SDL.h>

class ColliderComponent : public Component
{

public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceReactangle;
    SDL_Rect destinationRectangle;
    TransformComponent *transform;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
    {
        this->colliderTag = colliderTag;
        this->collider = {x, y, width, height};
    }

    void Initalise() override
    {
        if (owner->HasComponent<TransformComponent>())
        {
            transform = owner->GetComponent<TransformComponent>();
            sourceReactangle = {0, 0, transform->width, transform->height};
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Game::camera.x;
        destinationRectangle.y = collider.y - Game::camera.y;
    }
};

#endif // COLLIDERCOMPONENT_HPP