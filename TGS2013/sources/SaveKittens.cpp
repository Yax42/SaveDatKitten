
#include "SaveKittens.hh"
#include "assets.gen.h"

#include "Random.hh"

SaveKittens::SaveKittens() :
	_player(0, 0, _cubes, _cubes + 1, 0)
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
	_mode = DUEL;
	_duel.setCubes(_cubes, 0, _cubes + 2, 2);
	_player.updateChar();
	_map.printCase(_player);
	_player.drawer().initSort();
	_player.secondDrawer().initSort();
//	Sifteo::Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
	Sifteo::Events::cubeAccelChange.set(&SaveKittens::onCubeMove, this);
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
	if (_mode == EXPLORATION)
	{
		_player.update(dt);
		if (_player.shining)
			_player.follow(Paw, _kitty.character());
		else
			;//_player.follow(Mark, _player2);
		_player.flush();
		_kitty.update(dt);
	}
	else if (_mode == DUEL)
	{
		_duel.update(dt);
	}
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	if (_mode == EXPLORATION)
	{
		_player.connection(&_cubes[firstID], firstSide, &_cubes[secondID], secondSide);

		_player.drawer().clean();
		_map.printCase(_player);
		_player.drawer().initSort();
	}
	else if (_mode == DUEL)
	{
		
	}
}

void SaveKittens::onCubeMove(unsigned value)
{
	_duel.registerDirection(value);
}
