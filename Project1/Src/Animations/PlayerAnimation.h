#pragma once
#include <map>
#include "../ECS/AnimationComponent.h"

//AnimationType mAnimationType, const char* mPath, int f, int s)

class PlayerAnimation
{
private:

	Animation idle{ AnimationType::idle, "Assets/character/idle/", 3, 400 };
	Animation move{AnimationType::move, "Assets/character/run/k", 8, 100};

public:

	std::map<AnimationType, Animation> playerAnimationMap;

	PlayerAnimation()
	{
		playerAnimationMap.insert({ AnimationType::idle, idle });
		playerAnimationMap.insert({ AnimationType::move,move });
	}
};


