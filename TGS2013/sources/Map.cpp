#include "Map.hh"
#include "assets.gen.h"

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

void Map::chooseTreePositions(unsigned int x, unsigned int y, Sifteo::Random &random)
{
	unsigned int 	len;

	for (unsigned int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
	{
		random.seed();
		do
		{
			_map[y * MAP_SIZE + x].plants[i].pos.x = random.raw() % SCREEN_SIZE - TILE_SIZE / 2;
			_map[y * MAP_SIZE + x].plants[i].pos.y = random.raw() % SCREEN_SIZE - TILE_SIZE / 2;
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
			_map[y * MAP_SIZE + x].plants[i].frame = random.raw() % 10;
		else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
			_map[y * MAP_SIZE + x].plants[i].frame = 10 + random.raw() % 10;
		else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
			_map[y * MAP_SIZE + x].plants[i].frame = 20 + random.raw() % 10;
	}
}

void Map::genMap()
{
	SZone						zones[ZONE_NBR];
	Sifteo::Random				random;

	random.seed();
	for (unsigned int i = 0; i < ZONE_NBR; ++i)
	{
		zones[i].posX = random.raw() % MAP_SIZE;
		zones[i].posY = random.raw() % MAP_SIZE;
		zones[i].type = static_cast<EZoneType>(i % 3);
	}
	for (unsigned int y = 0; y < MAP_SIZE; ++y)
	{
		LOG("\n");
		for (unsigned int x = 0; x < MAP_SIZE; ++x)
		{
			_map[y * MAP_SIZE + x].type = checkZone(zones, x, y);
			_map[y * MAP_SIZE + x].plantNbr = random.raw() % MAX_PLANT_NBR;
			chooseTreePositions(x, y, random);
			if (_map[y * MAP_SIZE + x].type == ZONE_GRASS)
				LOG("G");
			else if (_map[y * MAP_SIZE + x].type == ZONE_SAND)
				LOG("S");
			else if (_map[y * MAP_SIZE + x].type == ZONE_ROCK)
				LOG("R");
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

bool Map::isInTab(unsigned char *tab, unsigned char size, unsigned char value) const
{
	for (unsigned char i = 0; i < size; ++i)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

void Map::printCase(Sifteo::VideoBuffer &buffer, SortSprites &drawer, unsigned int x, unsigned int y) const
{
	SortSprites::SSprite		sprite;

	for (int i = 0; i < _map[y * MAP_SIZE + x].plantNbr; ++i)
	{
		sprite.pos = _map[y * MAP_SIZE + x].plants[i].pos;
		sprite.frame = _map[y * MAP_SIZE + x].plants[i].frame;
		sprite.img = &Plants;
		drawer.addSprite(sprite);
	}
	buffer.bg0.image(Sifteo::vec(0, 0), GroundTiles, _map[y * MAP_SIZE + x].type);
	//for (unsigned int i = 0; i < 8; ++i)
		//buffer.sprites[i].setImage(Plants, 35);
	//drawSorted(buffer, &_map[y * MAP_SIZE + x].plants[0], _map[y * MAP_SIZE + x].plantNbr, x, y);
	if (x == 0)
		buffer.bg0.image(Sifteo::vec(0, 0), VerticalWall);
	else if (x == MAP_SIZE - 1)
		buffer.bg0.image(Sifteo::vec(SCREEN_SIZE / 8 - WALL_THICK / 8, 0), VerticalWall);
	if (y == 0)
		buffer.bg0.image(Sifteo::vec(0, 0), HorizontalWall);
	else if (y == MAP_SIZE - 1)
		buffer.bg0.image(Sifteo::vec(0, SCREEN_SIZE / 8 - WALL_THICK / 8), HorizontalWall);
}
