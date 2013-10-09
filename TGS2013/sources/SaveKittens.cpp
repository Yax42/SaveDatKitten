
#include "SaveKittens.hh"
#include "assets.gen.h"

SaveKittens::SaveKittens() :
	_player(0, 0, 0, 1)
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
	_map.printCase(_cubes[_player.cubeID()], _player.x(), _player.y(), true);
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	for (int i = 0; i < gNumCubes; ++i)
	{
		if (i != _player.cubeID())
			_map.printCase(_cubes[i], _player.x(), _player.y(), false);
	}
	_player.connection(firstID, firstSide, secondID, secondSide);
	_map.printCase(_cubes[_player.cubeID()], _player.x(), _player.y(), true);
	LOG("now in case %d %d\n", _player.x(), _player.y());
}
