
#include "SaveKittens.hh"
#include "assets.gen.h"

#include "Random.hh"


SaveKittens::SaveKittens() :
	_player(gRandom.random() * MAP_SIZE, gRandom.random() * MAP_SIZE, _cubes, 0),
	_player2(gRandom.random() * MAP_SIZE, gRandom.random() * MAP_SIZE, _cubes + 1, 1)
{
	_winner = NULL;
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
	//_mode = DUEL;
	_mode = EXPLORATION;
	_duel.setCubes(_cubes, 0, _cubes + 1, 1, &_player, &_player2);
	_player.updateChar();
	_player2.updateChar();
	_map.printCase(_player);
	_map.printCase(_player2);
	_player.drawer().initSort();
	_player2.drawer().initSort();
//	Sifteo::Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
	Sifteo::Events::cubeAccelChange.set(&SaveKittens::onCubeMove, this);
	Sifteo::Events::cubeTouch.set(&SaveKittens::onCubeTouch, this);
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
	if (_winner != NULL)
	{
		_player.cube().sprites[0].move(32, 32);
		_player.cube().sprites[0].setImage(Perdre, (_winner == &_player) ? 1 : 2);
		_player2.cube().sprites[0].move(32, 32);
		_player2.cube().sprites[0].setImage(Perdre, (_winner == &_player) ? 2 : 1);
	}
	else if (_mode == EXPLORATION)
	{
		_player.update(dt);
		_player2.update(dt);
		if (_player.shining)
			_player.follow(Paw, _kitty.character());
		else
			_player.follow(Shroom, _player2._char);
		if (_player2.shining)
			_player2.follow(Paw, _kitty.character());
		else
			_player2.follow(Flash, _player._char);
		_player.flush(_map);
		_player2.flush(_map);
		_kitty.update(dt);
		
	}
	else if (_mode == DUEL)
	{
		_duel.update(dt);
	}
}

void SaveKittens::onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
{
	return;

	if (_mode == EXPLORATION)
	{
		_player.move();
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

void SaveKittens::onCubeTouch(unsigned value)
{
	if (_winner)
	{
		_winner = NULL;
	}
	else if (value == 0 &&
		_player.x() / 128 == _kitty.character().x() / 128 &&
		_player.y() / 128 == _kitty.character().y() / 128)
		_winner = &_player;
	else if (value == 1 &&
		_player2.x() / 128 == _kitty.character().x() / 128 &&
		_player2.y() / 128 == _kitty.character().y() / 128)
		_winner = &_player2;
}
