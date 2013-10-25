
#include "SaveKittens.hh"
#include "assets.gen.h"

SaveKittens::SaveKittens() :
	_player(0, 0, &_cubes[0], &_cubes[1], 0)
{
	_map.genMap();
}

void SaveKittens::init()
{
	for (int i = 0; i < gNumCubes; ++i)
	{
		_cubes[i].initMode(Sifteo::BG0_SPR_BG1);
		_cubes[i].attach(i);
		_cubes[i].bg0.image(Sifteo::vec(0, 0), BlackTile);
	}
	_player.updateChar();
	Sifteo::Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
	_map.printCase(_player);
	_player.drawer().initSort();
	//_map.printCase(_player.cube(), _drawer, _player.x(), _player.y());
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
	_player.update(dt);
	_player.flush();
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	_player.connection(&_cubes[firstID], firstSide, &_cubes[secondID], secondSide);

	_player.drawer().clean();
	_map.printCase(_player);
	_player.drawer().initSort();

	//LOG("now in case %d %d\n", _player.x(), _player.y());
}
