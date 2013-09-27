#include "Map.hh"
#include "assets.gen.h"

const unsigned int	Map::size = MAP_SIZE;

Map::STile::STile()
{
	img = NULL;
}

Map::Map()
{
	genMap();
}

Map::~Map()
{
}

void Map::genMap()
{
	for (unsigned int i = 0; i < size * size; ++i)
	{
		_map[i].bg = i % 3;
	}
}

void Map::printCase(Sifteo::VideoBuffer &buffer, unsigned int x, unsigned int y)
{
	buffer.bg0.image(Sifteo::vec(0, 0), GroundTiles, _map[y * size + x].bg);
}
