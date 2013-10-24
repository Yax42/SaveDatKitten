#pragma once

#include <sifteo.h>
#include "SortSprites.hh"

class Player;

class Character
{
public:
	Character(const Sifteo::PinnedAssetImage &image, float x, float y, float maxSPeed);
	~Character() {}
	void			update(float delta);
	void			print(SortSprites &sprites, unsigned int x, unsigned int y);
	void			setGoal(float x, float y);
	bool			goalAlive() const;

private:
	const Sifteo::PinnedAssetImage	&_image;
	Sifteo::Float2					_pos;
	Sifteo::Float2					_goal;
	bool							_goalAlive;
	float							_maxSpeed;
	int								_spriteId;
};