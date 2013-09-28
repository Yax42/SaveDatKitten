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
	SZone						zones[ZONE_NBR];
	Sifteo::Random				random;

	random.seed();
	for (unsigned int i = 0; i < ZONE_NBR; ++i)
	{
		zones[i].posX = static_cast<unsigned int>(random.random() * MAP_SIZE);
		zones[i].posY = static_cast<unsigned int>(random.random() * MAP_SIZE);
		zones[i].type = static_cast<EZoneType>(i % 3);
	}
	for (unsigned int y = 0; y < MAP_SIZE; ++y)
	{
		LOG("\n");
		for (unsigned int x = 0; x < MAP_SIZE; ++x)
		{
			_map[y * MAP_SIZE + x].type = checkZone(zones, x, y);
			if (_map[y * MAP_SIZE + x].type == ZONE_GRASS)
				LOG("*");
			else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
				LOG("o");
			else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
				LOG("+");
		}
	}
}

Map::EZoneType Map::checkZone(SZone *zones, unsigned int x, unsigned int y) const
{
	unsigned int	nearestDist;
	EZoneType		nearest = ZONE_UNKNOWN;

	for (unsigned int i = 0; i < ZONE_NBR; ++i)
	{
		unsigned int	dist = ABS((zones[i].posX - x) * (zones[i].posX - x)) +
							   ABS((zones[i].posY - y) * (zones[i].posY - y));

		if (nearest == ZONE_UNKNOWN || dist <= nearestDist)
		{
			nearest = zones[i].type;
			nearestDist = dist;
		}
	}
	return (nearest);
}

void Map::printCase(Sifteo::VideoBuffer &buffer, unsigned int x, unsigned int y) const
{
	buffer.bg0.image(Sifteo::vec(0, 0), GroundTiles, _map[y * MAP_SIZE + x].type);
}
