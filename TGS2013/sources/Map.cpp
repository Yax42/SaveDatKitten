#include "Map.hh"
#include "assets.gen.h"

const unsigned int	Map::size = MAP_SIZE;

Map::Map()
{
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
			_map[y * MAP_SIZE + x].plantNbr = static_cast<unsigned int>(random.random() * 4);
			for (int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
			{
				_map[y * MAP_SIZE + x].plants[i].pos.x = static_cast<int>(random.random() * 128) - 32;
				_map[y * MAP_SIZE + x].plants[i].pos.y = static_cast<int>(random.random() * 128) - 32;
				if (x == 0 && _map[y * MAP_SIZE + x].plants[i].pos.x < 32)
					_map[y * MAP_SIZE + x].plants[i].pos.x = 32;
				else if (x == MAP_SIZE - 1 && _map[y * MAP_SIZE + x].plants[i].pos.x > 128 - 32 - 64)
					_map[y * MAP_SIZE + x].plants[i].pos.x = 128 - 32 - 64;
				if (y == MAP_SIZE - 1 && _map[y * MAP_SIZE + x].plants[i].pos.y > 128 - 32 - 64)
					_map[y * MAP_SIZE + x].plants[i].pos.y = 128 - 32 - 64;
				_map[y * MAP_SIZE + x].plants[i].frame = static_cast<unsigned int>(random.random() * 12);
			}
			if (_map[y * MAP_SIZE + x].type == ZONE_GRASS)
				LOG("*");
			else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
				LOG("o");
			else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
				LOG("+");
		}
	}
	LOG("\n");
}

Map::EZoneType Map::checkZone(SZone *zones, unsigned int x, unsigned int y) const
{
	unsigned int	nearestDist;
	EZoneType		nearest = ZONE_UNKNOWN;

	for (unsigned int i = 0; i < ZONE_NBR; ++i)
	{
		unsigned int	dist = ABS((zones[i].posX - x) * (zones[i].posX - x)) +
							   ABS((zones[i].posY - y) * (zones[i].posY - y));

		if (nearest == ZONE_UNKNOWN || dist < nearestDist)
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
	for (unsigned int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
	{
		buffer.sprites[i].move(_map[y * MAP_SIZE + x].plants[i].pos.x, _map[y * MAP_SIZE + x].plants[i].pos.y);
		buffer.sprites[i].setImage(Plants, _map[y * MAP_SIZE + x].plants[i].frame);
	}
	if (x == 0)
		buffer.bg0.image(Sifteo::vec(0, 0), VerticalWall);
	else if (x == MAP_SIZE - 1)
		buffer.bg0.image(Sifteo::vec(128 / 8 - 32 / 8, 0), VerticalWall);
	if (y == 0)
		buffer.bg0.image(Sifteo::vec(0, 0), HorizontalWall);
	else if (y == MAP_SIZE - 1)
		buffer.bg0.image(Sifteo::vec(0, 128 / 8 - 32 / 8), HorizontalWall);
}
