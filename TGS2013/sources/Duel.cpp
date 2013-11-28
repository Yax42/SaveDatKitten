
#include "Duel.hh"
#include "Map.hh"

#define MAX2(x, y) 		(x > y) ? (x) : (y)

Duel::Duel() :
	_player1Id(0),
	_player2Id(0),
	_player1(NULL),
	_player2(NULL),
	_winner(0),
	_currentNbr(0),
	_recordedNbr(0)
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
		LOG("ACCEL X = %d\n", accel.x);
		if (accel.x > 0)
			return (EDirection::LEFT);
		else
			return (EDirection::RIGHT);
	}
	else
	{
		LOG("ACCEL Y = %d\n", accel.y);
		if (accel.y > 0)
			return (EDirection::TOP);
		else
			return (EDirection::BOT);
	}
}

void 		Duel::registerDirection(unsigned int cubeId)
{
//	if (_winner)
//		return ;
	if (_player1Id == cubeId)
	{
		if (_recordedNbr == _currentNbr)
		{
			_recorded[_recordedNbr++] = getCubeOrientation(_player1);
			LOG("new direction recorded: %d\n", _recorded[_recordedNbr - 1]);
		}
		else if (_recorded[_recordedNbr] != getCubeOrientation(_player1))
		{
			LOG("You failed like a little bitch...\n");
			_winner = 2;
		}
		else
		{
			LOG("You succeed mother fucker!\n");
			_recordedNbr++;
		}
	}
	else if (_player2Id == cubeId)
	{
		if (_recordedNbr == _currentNbr)
		{
			_recorded[_recordedNbr++] = getCubeOrientation(_player2);
			LOG("new direction recorded: %d\n", _recorded[_recordedNbr - 1]);
		}
		else if (_recorded[_recordedNbr] != getCubeOrientation(_player2))
		{
			LOG("You failed like a little bitch...\n");
			_winner = 1;
		}
		else
		{
			LOG("You succeed mother fucker!\n");
			_recordedNbr++;
		}
	}
	if (_winner)
		LOG("YOUHOU! player %d won!\n", _winner);
}
