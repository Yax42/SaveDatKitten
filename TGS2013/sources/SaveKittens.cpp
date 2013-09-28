
#include "SaveKittens.hh"

SaveKittens::SaveKittens() :
	_player(16, 16, 0, 1)
{
	LOG("print: cube id = %d, pos = %d, %d\n", _player.cubeID(), _player.x(), _player.y());
	_map.printCase(_cubes[_player.cubeID()], _player.x(), _player.y());
}

void SaveKittens::init()
{
	for (int i = 0; i < gNumCubes; ++i)
	{
	       _cubes[i].initMode(Sifteo::BG0_SPR_BG1);
	       _cubes[i].attach(i);
	}
	Sifteo::Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	_player.connection(firstID, firstSide, secondID, secondSide);
	_map.printCase(_cubes[_player.cubeID()], _player.x(), _player.y());
	LOG("now in case %d %d\n", _player.x(), _player.y());
}
