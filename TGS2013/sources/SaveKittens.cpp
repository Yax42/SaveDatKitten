
#include "SaveKittens.hh"
#include "assets.gen.h"

SaveKittens::SaveKittens() :
	_player(0, 0, &_cubes[0], &_cubes[1])
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
	Sifteo::Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
	_map.printCase(_player.cube(), _drawer, _player.x(), _player.y());
	_drawer.flush(_player.cube());
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
	_player.update(dt);
	_player.print(_drawer, _player.x(), _player.y());
	_map.printCase(_player.cube(), _drawer, _player.x(), _player.y());
	_drawer.flush(_player.cube());
	if (_player.x() != _player.xOld() || _player.y() != _player.yOld())
	{
		_player.print(_drawer, _player.xOld(), _player.yOld());
		_map.printCase(_player.cubeOld(), _drawer, _player.xOld(), _player.yOld());
		_drawer.flush(_player.cubeOld());
	}
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	_player.connection(&_cubes[firstID], firstSide, &_cubes[secondID], secondSide);
	LOG("now in case %d %d\n", _player.x(), _player.y());
	_drawer.flush(_player.cube());
}
