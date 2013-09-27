#include "Map.hh"
#include "assets.gen.h"

const unsigned int	Map::size = 32;

Map::SCase::SCase()
{
	for (int i = 0; i < 8; ++i)
		tiles[i] = NULL;
}

Map::SCase::~SCase()
{
	for (int i = 0; i < 8; ++i)
		delete tiles[i];
}

Map::Map() :
	_map(NULL)
{
	genMap();
}

Map::~Map()
{
}

void Map::genMap()
{
	delete _map;
	_map = new SCase[size * size];
	for (unsigned int i = 0; i < size * size; ++i)
	{
		_map[i].bg = i % 3;
	}
}

void Map::printCase(Sifteo::VideoBuffer &buffer, unsigned int x, unsigned int y)
{
	buffer.bg0.image(Sifteo::vec(0, 0), GroundTiles, _map[y * size + x].bg);
}
