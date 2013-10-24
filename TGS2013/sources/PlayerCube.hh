#pragma once

#include "SortSprites.hh"

class PlayerCube
{
public:
	PlayerCube(Sifteo::VideoBuffer *cube);
	~PlayerCube() {}
	Sifteo::VideoBuffer *cube() { return (_cube); }
	SortSprites			&drawer() { return (_sprites); }

private:
	Sifteo::VideoBuffer		*_cube;
	SortSprites				_sprites;
};