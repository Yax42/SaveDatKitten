#pragma once

#include <sifteo.h>

#include "SortSprites.hh"
#include "Player.hh"

#define	MAP_SIZE		16
#define	ZONE_NBR		16
#define TILE_SIZE 		64
#define WALL_THICK 		32
#define SCREEN_SIZE 	128
#define MAX_PLANT_NBR	4
#define MAX_SPRITES 	8

#define ABS(x)	(((x) < 0) ? (-(x)) : (x))

class Map
{
public:
	static const unsigned int		size;

	Map();
	~Map();

	void printCase(Player &player) const;
	void genMap();
	
private:
	enum	EZoneType
	{
		ZONE_GRASS,
		ZONE_SAND,
		ZONE_ROCK,
		ZONE_UNKNOWN
	};

	struct	STile
	{
		Sifteo::Int2 		pos;
		unsigned char 		frame;
	};

	struct	SCase
	{
		EZoneType		type;
		unsigned char 	plantNbr;
		STile			plants[MAX_PLANT_NBR];
	};

	struct	SZone
	{
		unsigned int	posX, posY;
		EZoneType		type;
	};

	SCase			_map[MAP_SIZE * MAP_SIZE];

	EZoneType	checkZone(SZone *zones, unsigned int x, unsigned int y) const;
	bool		isInTab(unsigned char *tab, unsigned char size, unsigned char value) const;
	bool		getNearestTree(unsigned int curIdx, unsigned int x, unsigned int y, unsigned int limit);
	void		chooseTreePositions(unsigned int x, unsigned int y, Sifteo::Random &random);
};