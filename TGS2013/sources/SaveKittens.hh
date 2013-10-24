#pragma once

#include <sifteo.h>

#include "Map.hh"
#include "Player.hh"
#include "SortSprites.hh"

static const unsigned int gNumCubes = 3;

class SaveKittens
{
private:   
    Sifteo::VideoBuffer _cubes[gNumCubes];
	Map					_map;
	Player				_player;

public:
	SaveKittens();
	~SaveKittens() { }

    void init();
	void update(Sifteo::TimeDelta dt);
	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);
};