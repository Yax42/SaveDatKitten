#include "Player.hh"
#include "Map.hh"
#include "assets.gen.h"

Player::Player(int x, int y, PlayerCube mainCube, PlayerCube sideCube, int id) : _x(x), _y(y), _xOld(x), _yOld(y),
	_mainCube(mainCube), _sideCube(sideCube), _char(Pikachu, x * Sifteo::LCD_width, y * Sifteo::LCD_height, 100)
{
	SortSprites::characters[id] = &_char;
    clampPosition();
}

Player::~Player(){}

void		Player::connection(Sifteo::VideoBuffer *cube1, unsigned int side1, Sifteo::VideoBuffer *cube2, unsigned int side2)
{
	int		mainSide;
	int		sideSide;
	Sifteo::Random				random;
	random.seed();

	if (cube1 == _mainCube.cube() && cube2 == _sideCube.cube())
	{
		mainSide = side1;
		sideSide = side2;
	}
	else if (cube2 == _mainCube.cube() && cube1 == _sideCube.cube())
	{
		mainSide = side2;
		sideSide = side1;
	}
	else
		return ;
	_char.setGoal(_x * Sifteo::LCD_width + 32 + static_cast<unsigned int>(random.random() * 32),
				_y * Sifteo::LCD_height + static_cast<unsigned int>(random.random() * 64));
	//gerrer l'orientation des cubes
	move(mainSide);
}


/******PRIVATE******/
bool	Player::clampPosition()
{
    bool	change = false;

    if (_x < 0)
    {
		_x = 0;
		_xOld = _x + 1;
		change = true;
    }
    else if (_x >= Map::size)
    {
		_x = Map::size - 1;
		_xOld = _x - 1;
		change = true;
    }
    if (_y < 0)
    {
		_y = 0;
		_yOld = _y + 1;
		change = true;
    }
    else if (_y >= Map::size)
    {
		_y = Map::size - 1;
		_yOld = _y - 1;
		change = true;
    }
    return (change);
}

void		Player::swapCubes()
{
    PlayerCube		tmp = _mainCube;
    _mainCube = _sideCube;
    _sideCube = tmp;
}

void		Player::move(int dir)
{
    if (dir == EDirection::LEFT)
	{
		_xOld = _x;
		_x++;
	}
    if (dir == EDirection::TOP)
	{
		_yOld = _y;
		_y++;
	}
    if (dir == EDirection::RIGHT)
	{
		_xOld = _x;
		_x--;
	}
    if (dir == EDirection::BOT)
	{
		_yOld = _y;
		_y--;
	}
    if (clampPosition() == false)
	swapCubes();
}

void					Player::flush()
{
	_sideCube.drawer().updateCharacters(_x, _y);
    _mainCube.drawer().flush();
	_sideCube.drawer().updateCharacters(_xOld, _yOld);
    _sideCube.drawer().flush();
}

void					Player::updateChar()
{
    _mainCube.drawer().setCharacters();
    _sideCube.drawer().setCharacters();
}