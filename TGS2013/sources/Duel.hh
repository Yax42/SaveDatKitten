#ifndef 	DUEL_HH_
# define 	DUEL_HH_

#include 	"Player.hh"

class 	Duel
{
private:
	unsigned int 			_player1Id;
	unsigned int 			_player2Id;
	Sifteo::VideoBuffer 	*_player1;
	Sifteo::VideoBuffer 	*_player2;

	unsigned int 			_winner;
	
	unsigned int 			_currentNbr;
	EDirection::EDirection 	_recorded[24];
	unsigned int 			_recordedNbr;
	
	unsigned int  			_currentPlayer;
	
	EDirection::EDirection 	_lastDirection;

	void 					printLastDirection(Sifteo::VideoBuffer *player);
	
public:
	Duel();
	~Duel();
	
	void 					setCubes(Sifteo::VideoBuffer *player1, unsigned int player1Id,
									 Sifteo::VideoBuffer *player2, unsigned int player2Id);
	EDirection::EDirection 	getCubeOrientation(Sifteo::VideoBuffer *player);
	void 					update(float deltaTime) { }
	void 					registerDirection(unsigned int cubeId);
};

#endif