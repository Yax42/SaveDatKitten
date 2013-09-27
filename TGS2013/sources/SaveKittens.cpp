
#include "SaveKittens.hh"

SaveKittens::SaveKittens() :
	_player(16, 16, 0, 1)
{
}

void SaveKittens::init()
{
	for (int i = 0; i < gNumCubes; ++i)
	{
	       _cubes[i].initMode(BG0_SPR_BG1);
	       _cubes[i].attach(i);
	}
	Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
}

void SaveKittens::update(TimeDelta dt)
{
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	_player.connection(firstID, firstSide, secondID, secondSide);
	_map.printCase(_cubes[_player.cubeID()], _player.x(), _player.y());
}
