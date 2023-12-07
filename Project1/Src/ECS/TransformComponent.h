#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent: public Component
{

public:

	Vector2D position;
	Vector2D velocity;
	
	int height = 64;
	int width = 64;
	int scale = 1;

	int speed = 3;

	void init() override
	{
		velocity.Zero();
	}

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y,int h, int w,int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void update()
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};

