#pragma once

#include <sifteo.h>

#define	MAP_SIZE	16
#define	ZONE_NBR	16

#define ABS(x)	(((x) < 0) ? (-(x)) : (x))

class Map
{
public:
	static const unsigned int		size;

	Map();
	~Map();

	void printCase(Sifteo::VideoBuffer &buffer, unsigned int x, unsigned int y) const;
	void genMap();
	
private:

	enum	EZoneType
	{
		ZONE_SAND,
		ZONE_GRASS,
		ZONE_ROCK,
		ZONE_UNKNOWN
	};

	struct	STile
	{
		Sifteo::Int2 		pos;
		unsigned int 		frame;
	};

	struct	SCase
	{
		EZoneType		type;
		unsigned int 	plantNbr;
		STile			plants[4];
	};

	struct	SZone
	{
		unsigned int	posX, posY;
		EZoneType		type;
	};

	SCase			_map[MAP_SIZE * MAP_SIZE];

	EZoneType checkZone(SZone *zones, unsigned int x, unsigned int y) const;
};