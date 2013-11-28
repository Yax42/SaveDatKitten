
#include "Duel.hh"
#include "Map.hh"

#include "assets.gen.h"

#define MAX2(x, y) 		(x > y) ? (x) : (y)

Duel::Duel() :
	_player1Id(0),
	_player2Id(0),
	_player1(NULL),
	_player2(NULL),
	_winner(0),
	_currentNbr(0),
	_recordedNbr(0),
	_lastDirection(EDirection::IDLE)
{
}

Duel::~Duel()
{
}

void 		Duel::setCubes(Sifteo::VideoBuffer *player1, unsigned int player1Id,
							Sifteo::VideoBuffer *player2, unsigned int player2Id)
{
	_player1Id = player1Id;
	_player2Id = player2Id;
	_player1 = player1;
	_player2 = player2;
	_currentNbr = 0;
}

EDirection::EDirection 	Duel::getCubeOrientation(Sifteo::VideoBuffer *player)
{
	Sifteo::Int2 	accel = player->physicalAccel().xy();
	
	if (MAX2(ABS(accel.x), ABS(accel.y)) == ABS(accel.x))
	{
		if (ABS(accel.x) < 50)
			return (EDirection::IDLE);
		else if (accel.x > 0)
			return (EDirection::LEFT);
		else
			return (EDirection::RIGHT);
	}
	else
	{
		if (ABS(accel.y) < 50)
			return (EDirection::IDLE);
		else if (accel.y > 0)
			return (EDirection::TOP);
		else
			return (EDirection::BOT);
	}
}

void 		Duel::printLastDirection(Sifteo::VideoBuffer *player)
{
	if (_lastDirection == EDirection::IDLE)
	{
		player->sprites[0].setImage(Empty, 0);
	}
	else if (_lastDirection == EDirection::TOP)
	{
		player->sprites[0].move(0, 0);
		player->sprites[0].setImage(UpDown, 0);
	}
	else if (_lastDirection == EDirection::BOT)
	{
		player->sprites[0].move(0, 128 - 32);
		player->sprites[0].setImage(UpDown, 1);
	}
	else if (_lastDirection == EDirection::LEFT)
	{
		player->sprites[0].move(0, 0);
		player->sprites[0].setImage(LeftRight, 0);
	}
	else if (_lastDirection == EDirection::RIGHT)
	{
		player->sprites[0].move(128 - 32, 0);
		player->sprites[0].setImage(LeftRight, 1);
	}
}

void 		Duel::registerDirection(unsigned int cubeId)
{
	EDirection::EDirection	curDir;
	Sifteo::VideoBuffer 	*buff;

//	if (_winner)
//		return ;
	if (cubeId == _player1Id)
		buff = _player1;
	else if (cubeId == _player2Id)
		buff = _player2;
	curDir = getCubeOrientation(buff);
	if (curDir == EDirection::IDLE || _lastDirection == curDir)
	{
		_lastDirection = curDir;
		return ;
	}
	_lastDirection = curDir;
	printLastDirection(buff);
	if (_recordedNbr == _currentNbr)
	{
		_recorded[_recordedNbr] = _lastDirection;
		LOG("new direction recorded: %d\n", _recorded[_recordedNbr]);
		++_currentNbr;
		++_recordedNbr;
	}
	else if (_recorded[_recordedNbr] != _lastDirection)
	{
		LOG("You failed like a little bitch...\n");
		_winner = 2;
	}
	else
	{
		LOG("You succeed mother fucker!\n");
		_recordedNbr++;
	}
	if (_winner)
		LOG("YOUHOU! player %d won!\n", _winner);
}
