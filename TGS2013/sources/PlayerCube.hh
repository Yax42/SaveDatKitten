#pragma once

class PlayerCube
{
public:
	PlayerCube(Sifteo::VideoBuffer *cube);
	~PlayerCube() {}
	operator Sifteo::VideoBuffer &() { return (*_cube); }
	SortSprites			&drawer() { return (_sprites); }

private:
	Sifteo::VideoBuffer		*_cube;
	SortSprites				_sprites;
};