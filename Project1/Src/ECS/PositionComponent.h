#pragma once
#include "ECS.h"

class PositionComponent: public Component
{

private:
	int xpos;
	int ypos;

public:

	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	PositionComponent()
	{
		init();
	}

	PositionComponent(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	int x() { return xpos; }
	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }



	void SetPosition(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	void update()
	{
		xpos++;
		ypos++;
	}

};

