
#include "Duel.hh"
#include "Map.hh"

#include "assets.gen.h"

#define MAX2(x, y) 		(x > y) ? (x) : (y)

#define	ORIENTTHRESHOLD 		40
#define CHANGE_PLAYER_TIME 		1
#define WON_TIME 				3

Duel::Duel() :
	_changePlayer(false),
	_timer(0),
	_player1Id(0),
	_player2Id(0),
	_player1(NULL),
	_player2(NULL),
	_winner(-1),
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
	_currentPlayer = _player1Id;
	LOG("Current player: %d\n", _currentPlayer);
}

EDirection::EDirection 	Duel::getCubeOrientation(Sifteo::VideoBuffer *player)
{
	Sifteo::Int2 	accel = player->physicalAccel().xy();
	
	if (MAX2(ABS(accel.x), ABS(accel.y)) == ABS(accel.x))
	{
		if (ABS(accel.x) < ORIENTTHRESHOLD)
			return (EDirection::IDLE);
		else if (accel.x > 0)
			return (EDirection::RIGHT);
		else
			return (EDirection::LEFT);
	}
	else
	{
		if (ABS(accel.y) < ORIENTTHRESHOLD)
			return (EDirection::IDLE);
		else if (accel.y > 0)
			return (EDirection::BOT);
		else
			return (EDirection::TOP);
	}
}

void 		Duel::printLastDirection()
{
	if (_lastDirection == EDirection::IDLE)
	{
		_player1->sprites[0].setImage(Empty, 0);
		_player2->sprites[0].setImage(Empty, 0);
	}
	else if (_lastDirection == EDirection::TOP)
	{
		_player1->sprites[0].move(0, 0);
		_player1->sprites[0].setImage(UpDown, 0);
		_player2->sprites[0].move(0, 0);
		_player2->sprites[0].setImage(UpDown, 0);
	}
	else if (_lastDirection == EDirection::BOT)
	{
		_player1->sprites[0].move(0, 128 - 32);
		_player1->sprites[0].setImage(UpDown, 1);
		_player2->sprites[0].move(0, 128 - 32);
		_player2->sprites[0].setImage(UpDown, 1);
	}
	else if (_lastDirection == EDirection::LEFT)
	{
		_player1->sprites[0].move(0, 0);
		_player1->sprites[0].setImage(LeftRight, 0);
		_player2->sprites[0].move(0, 0);
		_player2->sprites[0].setImage(LeftRight, 0);
	}
	else if (_lastDirection == EDirection::RIGHT)
	{
		_player1->sprites[0].move(128 - 32, 0);
		_player1->sprites[0].setImage(LeftRight, 1);
		_player2->sprites[0].move(128 - 32, 0);
		_player2->sprites[0].setImage(LeftRight, 1);
	}
}

void 		Duel::update(float deltaTime)
{
	if (_changePlayer)
	{
		_timer += deltaTime;
		if (_timer > CHANGE_PLAYER_TIME)
		{
			_currentPlayer = (_currentPlayer == _player1Id) ? (_player2Id) : (_player1Id);
			_player2->sprites[0].setImage(Empty, 0);
			_player1->sprites[0].setImage(Empty, 0);
			_timer = 0;
			_changePlayer = false;
		}
	}
	if (_winner != -1)
	{
		_timer += deltaTime;
		if (_timer > WON_TIME)
		{
			_timer = 0;
			_winner = -1;
			_player1->sprites[0].setImage(Empty, 0);
			_player2->sprites[0].setImage(Empty, 0);
		}
	}
}

void 		Duel::registerDirection(unsigned int cubeId)
{
	EDirection::EDirection	curDir;
	Sifteo::VideoBuffer 	*buff;

	if (_winner != -1 || _currentPlayer != cubeId || _changePlayer == true)
		return ;
	if (_currentPlayer == _player1Id)
		buff = _player1;
	else if (_currentPlayer == _player2Id)
		buff = _player2;
	curDir = getCubeOrientation(buff);
	if (curDir == EDirection::IDLE)
	{
		_lastDirection = curDir;
		_player1->sprites[0].setImage(Empty, 0);
		_player2->sprites[0].setImage(Empty, 0);
		return ;
	}
	else if (_lastDirection == curDir)
		return;
	_lastDirection = curDir;
	printLastDirection();
	if (_recordedNbr == _currentNbr) // The player register a new side
	{
		_recorded[_recordedNbr] = _lastDirection;
		_currentNbr = 0;
		_changePlayer = true;
		++_recordedNbr;
	}
	else if (_recorded[_currentNbr] != _lastDirection) // the player failed to find the right side
	{
		_winner = (_currentPlayer == _player1Id) ? (_player2Id) : (_player1Id);
		++_currentNbr;
	}
	else // the player succeed
	{
		++_currentNbr;
	}
	if (_winner != -1)
	{
		_player1->sprites[0].move(32, 32);
		_player1->sprites[0].setImage(SuccessFail, (_winner == _player1Id) ? 0 : 1);
		_player2->sprites[0].move(32, 32);
		_player2->sprites[0].setImage(SuccessFail, (_winner == _player1Id) ? 1 : 0);
	}
}
