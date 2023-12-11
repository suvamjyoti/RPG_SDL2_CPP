#pragma once

#include "ECS.h"
#include <map>

enum  AnimationType
{
	idle,
	move,
	dash,
	attack
};

struct Animation
{
	AnimationType animationType;
	const char* path;
	int frame;
	int speed;
	bool initialised = false;

	Animation() {}

	Animation(AnimationType mAnimationType, const char* mPath, int f, int s)
	{
		initialised = true;
		mAnimationType = animationType;
		path = mPath;
		frame = f;
		speed = s;
	}
};

class AnimationComponent : public Component
{
private:

public:

	std::map<AnimationType, Animation> AnimationsMap;		//will contain all possible animation for an entity
	Animation currentAnimation;							// the animation currently playing

	AnimationComponent() {};

	AnimationComponent(std::map<AnimationType, Animation>& mAnimationsMap,AnimationType startingAnimation)
		: AnimationsMap(mAnimationsMap)
	{
		auto it = AnimationsMap.find(startingAnimation);

		if (it != AnimationsMap.end())
		{
			currentAnimation = it->second;
		}
	}

	void init() override
	{

	}

	void update() override
	{
		if (currentAnimation.initialised)
		{
			std::string mFilePath = currentAnimation.path;
			mFilePath += std::to_string((SDL_GetTicks() / currentAnimation.speed) % currentAnimation.frame);
			mFilePath += ".png";

			entity_p->getComponent<SpriteComponent>().SetTeture(mFilePath.c_str());
		}
		
	}

	void SetAnimation(AnimationType animationType)
	{
		auto it = AnimationsMap.find(animationType);

		if (it != AnimationsMap.end()) {

			if (currentAnimation.animationType != animationType)
			{
				currentAnimation = it->second; 
				currentAnimation.animationType = animationType;
			}
		}
		else
		{
			std::cout << "Trying to set currentAnimation to a Animation not Found in map" << std::endl;
		}
	}

};