#pragma once

#include <sifteo.h>

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
		Sifteo::AssetImage	&img;
	};

	struct	SCase
	{
		unsigned int	bg;
		STile			*tiles[8];

		SCase();
		~SCase();
	};

	SCase		*_map;
};