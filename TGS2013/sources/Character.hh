#pragma once

#include <sifteo.h>
#include <sifteo/math.h>


class Character
{
public:
	Character(const Sifte::AssetImage &image, float x, float y, float maxSPeed);
	~Character() {}
	void			Update(float delta);
	void			print();
	void			setGoal(const Sifteo::Float2 &newGoal);
	bool			goalAlive() const;

private:
	const Sifte::AssetImage	    &_image;
	Sifteo::Float2				_pos;
	Sifteo::Float2				_goal;
	bool						_goalAlive;
	float						_maxSpeed;
	int							_spriteId;
};