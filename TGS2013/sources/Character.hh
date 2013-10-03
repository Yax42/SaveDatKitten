#pragma once

#include <sifteo.h>
#include <Vector2.hh>


class Character
{
public:
	Character(Sifte::assertImageint x, int y);

	~Character() {}

private:
	Vector2<float>	    _pos;
	Vector2<float>	    _speed;
	Vector2<float>	    _goal;
};