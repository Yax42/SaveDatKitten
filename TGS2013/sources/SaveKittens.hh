#pragma once

#include <sifteo.h>

#include "Map.hh"
#include "Player.hh"
#include "SortSprites.hh"
#include "Kitty.hh"
#include "Duel.hh"

static const unsigned int gNumCubes = 3;

class SaveKittens
{
public:
	enum 	EGameMode
	{
		EXPLORATION,
		DUEL
	};

private:   
	Player 				*_winner;

	Player				_player;
	Player				_player2;
//	SortSprites				catDrawer;
	Kitty				_kitty;
    Sifteo::VideoBuffer _cubes[gNumCubes];
	Map					_map;

	EGameMode 			_mode;
	Duel 				_duel;
	
public:
	SaveKittens();
	~SaveKittens() { }

    void init();
	void update(Sifteo::TimeDelta dt);
	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);
	void onCubeMove(unsigned int value);
	void onCubeTouch(unsigned int value);
};