#pragma once

#include <sifteo.h>

#define	MAP_SIZE	16

class Map
{
public:
	static const unsigned int		size;

	Map();
	~Map();

	void printCase(Sifteo::VideoBuffer &buffer, unsigned int x, unsigned int y);
	void genMap();

private:
	struct	STile
	{
		int					x, y;
		Sifteo::AssetImage	*img;
		
		STile();
	};

	struct	SCase
	{
		unsigned int	bg;
		STile			tiles[8];
	};

	SCase		_map[MAP_SIZE * MAP_SIZE];
};