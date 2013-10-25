#pragma once

#include <sifteo.h>

class Player;
class SortSprites;

class Character
{
public:
	Character(const Sifteo::PinnedAssetImage &image, float x, float y, float maxSPeed);
	~Character() {}
	void							update(float delta);
	void							print(SortSprites &sprites, unsigned int x, unsigned int y);
	void							setGoal(float x, float y);
	bool							goalAlive() const;
	int								frame() { return (_spriteId); }
	const Sifteo::PinnedAssetImage	*image() { return (&_image); }
	int								x() { return (static_cast<int>(_pos.x)); }
	int								y() { return (static_cast<int>(_pos.y)); }

private:
	const Sifteo::PinnedAssetImage	&_image;
	Sifteo::Float2					_pos;
	Sifteo::Float2					_goal;
	bool							_goalAlive;
	float							_maxSpeed;
	int								_spriteId;
};