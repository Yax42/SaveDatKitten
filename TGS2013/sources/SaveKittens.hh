#pragma once

#include <sifteo.h>

#include "Map.hh"
#include "Player.hh"
#include "SortSprites.hh"
#include "Kitty.hh"

static const unsigned int gNumCubes = 3;

class SaveKittens
{
private:   
	Player				_player;
	Kitty				_kitty;
    Sifteo::VideoBuffer _cubes[gNumCubes];
	Map					_map;

public:
	SaveKittens();
	~SaveKittens() { }

    void init();
	void update(Sifteo::TimeDelta dt);
	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide);
};