#include "Map.hh"
#include "assets.gen.h"

#include "Random.hh"

const unsigned int	Map::size = MAP_SIZE;

Map::Map()
{
}

Map::~Map()
{
}

bool Map::getNearestTree(unsigned int curIdx, unsigned int x, unsigned int y, unsigned int limit)
{
	for (unsigned int j = 0; j < curIdx; ++j)
	{
		Sifteo::Int2 	vec;
	
		vec = _map[y * MAP_SIZE + x].plants[curIdx].pos - _map[y * MAP_SIZE + x].plants[j].pos;
		if (static_cast<unsigned int>(vec.lenManhattan()) < limit)
			return (true);
	}
	return (false);
}

void Map::chooseTreePositions(unsigned int x, unsigned int y)
{
	unsigned int 	len;

	for (unsigned int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
	{
		do
		{
			_map[y * MAP_SIZE + x].plants[i].pos.x = gRandom.raw() % SCREEN_SIZE - TILE_SIZE / 2;
			_map[y * MAP_SIZE + x].plants[i].pos.y = gRandom.raw() % SCREEN_SIZE - TILE_SIZE / 3;
			if (x == 0 && _map[y * MAP_SIZE + x].plants[i].pos.x < WALL_THICK)
				_map[y * MAP_SIZE + x].plants[i].pos.x = WALL_THICK;
			else if (x == MAP_SIZE - 1 && _map[y * MAP_SIZE + x].plants[i].pos.x > SCREEN_SIZE - WALL_THICK - TILE_SIZE)
				_map[y * MAP_SIZE + x].plants[i].pos.x = SCREEN_SIZE - WALL_THICK - TILE_SIZE;
			if (y == 0 && _map[y * MAP_SIZE + x].plants[i].pos.y < -TILE_SIZE / 2 + 10)
				_map[y * MAP_SIZE + x].plants[i].pos.y = SCREEN_SIZE - WALL_THICK - TILE_SIZE;
			else if (y == MAP_SIZE - 1 && _map[y * MAP_SIZE + x].plants[i].pos.y > SCREEN_SIZE - WALL_THICK - TILE_SIZE)
				_map[y * MAP_SIZE + x].plants[i].pos.y = SCREEN_SIZE - WALL_THICK - TILE_SIZE;
		} while (getNearestTree(i, x, y, 30));
		// choose tile for zone
		if (_map[y * MAP_SIZE + x].type == ZONE_GRASS)
			_map[y * MAP_SIZE + x].plants[i].frame = gRandom.raw() % TREE_SPRITE_NBR;
		else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
			_map[y * MAP_SIZE + x].plants[i].frame = TREE_SPRITE_NBR + gRandom.raw() % TREE_SPRITE_NBR;
		else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
			_map[y * MAP_SIZE + x].plants[i].frame = 2 * TREE_SPRITE_NBR + gRandom.raw() % TREE_SPRITE_NBR;
	}
}

void Map::genMap()
{
	SZone						zones[ZONE_NBR];

	for (unsigned int i = 0; i < ZONE_NBR; ++i)
	{
		zones[i].posX = gRandom.raw() % MAP_SIZE;
		zones[i].posY = gRandom.raw() % MAP_SIZE;
		zones[i].type = static_cast<EZoneType>(i % 3);
	}
	for (unsigned int y = 0; y < MAP_SIZE; ++y)
	{
		for (unsigned int x = 0; x < MAP_SIZE; ++x)
		{
			_map[y * MAP_SIZE + x].type = checkZone(zones, x, y);
			_map[y * MAP_SIZE + x].plantNbr = gRandom.raw() % MAX_PLANT_NBR;
			chooseTreePositions(x, y);
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

		if (nearest == ZONE_UNKNOWN || dist < nearestDist)
		{
			nearest = zones[i].type;
			nearestDist = dist;
		}
	}
	return (nearest);
}

bool Map::isInTab(unsigned char *tab, unsigned char size, unsigned char value) const
{
	for (unsigned char i = 0; i < size; ++i)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

void Map::printCase(Player &player) const
{
	unsigned int				x = static_cast<unsigned int>(player.x());
	unsigned int				y = static_cast<unsigned int>(player.y());
	Sifteo::AssetImage const 	*image;
	
	for (int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
	{
		player.drawer().addSprite(_map[y * MAP_SIZE + x].plants[i].pos.x,
						 _map[y * MAP_SIZE + x].plants[i].pos.y,
						 _map[y * MAP_SIZE + x].plants[i].frame,
						 &Plants);
	}
	if (_map[y * MAP_SIZE + x].type == ZONE_GRASS)
		image = &GrassTile;
	else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
		image = &SandTile;
	else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
		image = &RockTile;
	player.cube().bg0.image(Sifteo::vec(0, 0), *image);
	if (x == 0)
		player.cube().bg0.image(Sifteo::vec(0, 0), VerticalWall);
	else if (x == MAP_SIZE - 1)
		player.cube().bg0.image(Sifteo::vec(SCREEN_SIZE / 8 - WALL_THICK / 8, 0), VerticalWall);
	if (y == 0)
		player.cube().bg0.image(Sifteo::vec(0, 0), HorizontalWall);
	else if (y == MAP_SIZE - 1)
		player.cube().bg0.image(Sifteo::vec(0, SCREEN_SIZE / 8 - WALL_THICK / 8), HorizontalWall);
}
