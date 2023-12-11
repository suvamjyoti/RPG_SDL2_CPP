#pragma once

#include "../Game.h"
#include "ECS.h"
//#include "Components.h"
#include "AnimationComponent.h"
#include "TransformComponent.h" 

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	AnimationComponent* animation;
	bool isMoving;
	
	void init() override
	{
		transform = &entity_p->getComponent<TransformComponent>();
		animation = &entity_p->getComponent<AnimationComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
				case SDLK_w:
					transform->velocity.y = -1;
					isMoving = true;
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					isMoving = true;
					break;
				case SDLK_s:
					transform->velocity.y = 1;
					isMoving = true;
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					isMoving = true;
					break;
				default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				isMoving = false;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				isMoving = false;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				isMoving = false;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				isMoving = false;
				break;
			default:
				break;
			}
		}

		if (isMoving)
		{
			animation->SetAnimation(AnimationType::move);
		}
		else
		{
			animation->SetAnimation(AnimationType::idle);
		}
		
	}
};