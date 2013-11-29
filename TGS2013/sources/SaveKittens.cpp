#include "SaveKittens.hh"
#include "assets.gen.h"

#include "Random.hh"


SaveKittens::SaveKittens() :
	_player(gRandom.random() * MAP_SIZE, gRandom.random() * MAP_SIZE, _cubes, 0),
	_player2(gRandom.random() * MAP_SIZE, gRandom.random() * MAP_SIZE, _cubes + 1, 1),
	_mode(EXPLORATION),
	_duel(&_mode)
{
	_winner = NULL;
	_map.genMap();
	_timer = 0;
}

void SaveKittens::init()
{
	for (int i = 0; i < gNumCubes; ++i)
	{
		_cubes[i].initMode(Sifteo::BG0_SPR_BG1);
		_cubes[i].attach(i);
		_cubes[i].bg0.image(Sifteo::vec(0, 0), BlackTile);
	}
	_duel.setCubes(_cubes, 0, _cubes + 1, 1, &_player, &_player2);
	_player.updateChar();
	_player2.updateChar();
	_map.printCase(_player);
	_map.printCase(_player2);
	_player.drawer().initSort();
	_player2.drawer().initSort();
	Sifteo::Events::cubeAccelChange.set(&SaveKittens::onCubeMove, this);
	Sifteo::Events::cubeTouch.set(&SaveKittens::onCubeTouch, this);
}

void SaveKittens::reset()
{
	_winner = NULL;
	_map.genMap();

	_player.shining = false;
	_player._x = gRandom.random() * MAP_SIZE;
	_player._y = gRandom.random() * MAP_SIZE;
	_player._xOld = -1;
	_player._yOld = -1;

	_player2.shining = false;
	_player2._x = gRandom.random() * MAP_SIZE;
	_player2._y = gRandom.random() * MAP_SIZE;
	_player2._xOld = -1;
	_player2._yOld = -1;
}

void SaveKittens::update(Sifteo::TimeDelta dt)
{
	if (_winner != NULL)
	{
		_player.cube().sprites[0].move(32, 32);
		_player.cube().sprites[0].setImage(Perdre, (_winner == &_player) ? 1 : 2);
		_player2.cube().sprites[0].move(32, 32);
		_player2.cube().sprites[0].setImage(Perdre, (_winner == &_player) ? 2 : 1);
		_timer += dt;
		if (_timer > RESET_GAME_TIME)
		{
			_timer = 0;
			reset();
		}
	}
	else if (_mode == EXPLORATION || _mode == FINDKITTEN)
	{
		_player.update(dt);
		_player2.update(dt);
		if (_player.shining)
			_player.follow(Paw, _kitty.character());
		else
			_player.follow(Flash, _player2._char);
		if (_player2.shining)
			_player2.follow(Paw, _kitty.character());
		else
			_player2.follow(Shroom, _player._char);
		_player.flush(_map);
		_player2.flush(_map);
		_kitty.update(dt);
		if (_player.x() == _player2.x() &&
			_player.y() == _player2.y() &&
			_mode != FINDKITTEN)
		{
			_duel.reset();
			_mode = DUEL;
		}
		else if (_mode == FINDKITTEN)
		{
			_timer += dt;
			if (_timer > TIME_SAVE_KITTEN)
			{
				_timer = 0;
				_mode = EXPLORATION;
				_player.shining = false;
				_player2.shining = false;
			}
		}
	}
	else if (_mode == DUEL)
	{
		_duel.update(dt);
	}
}

void SaveKittens::onCubeMove(unsigned value)
{
	_duel.registerDirection(value);
}

void SaveKittens::onCubeTouch(unsigned value)
{
	_timer = 0;
	if (value == 0 &&
		_player.x() == _kitty.character().x() / 128 &&
		_player.y() == _kitty.character().y() / 128)
		_winner = &_player;
	else if (value == 1 &&
		_player2.x() == _kitty.character().x() / 128 &&
		_player2.y() == _kitty.character().y() / 128)
		_winner = &_player2;
}
