#ifndef 	DUEL_HH_
# define 	DUEL_HH_

#include 	"Player.hh"

class 	Duel
{
private:	
	bool 					_enteringMode;
	
	bool 					_changePlayer;
	float 					_timer;

	unsigned int 			_player1Id;
	unsigned int 			_player2Id;
	Sifteo::VideoBuffer 	*_player1;
	Sifteo::VideoBuffer 	*_player2;
	Player					*_p1;
	Player					*_p2;

	unsigned int 			_winner;
	
	unsigned int 			_currentNbr;
	EDirection::EDirection 	_recorded[32];
	unsigned int 			_recordedNbr;
	
	unsigned int  			_currentPlayer;
	
	EDirection::EDirection 	_lastDirection;
	
	int 					*_gameMode;

	void 					printLastDirection();	
	
public:
	Duel(int *gameMode);
	~Duel();

	void 					reset();
	void 					setCubes(Sifteo::VideoBuffer *player1, unsigned int player1Id,
									 Sifteo::VideoBuffer *player2, unsigned int player2Id,
									 Player *p1, Player *p2);
	EDirection::EDirection 	getCubeOrientation(Sifteo::VideoBuffer *player);
	void 					update(float deltaTime);
	void 					registerDirection(unsigned int cubeId);
};

#endif