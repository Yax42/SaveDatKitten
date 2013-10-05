#include "Player.hh"
#include "Map.hh"
#include "assets.gen.h"

Player::Player(int x, int y, PlayerCube mainCube, PlayerCube sideCube) : _x(x), _y(y),
	_mainCube(mainCube), _sideCube(sideCube), _char(Pikachu, x * Sifteo::LCD_width, y * Sifteo::LCD_height, 5)
{
    clampPosition();
}

Player::~Player(){}

void		Player::connection(PlayerCube cube1, unsigned int side1, PlayerCube cube2, unsigned int side2)
{
	int		mainSide;
	int		sideSide;
	Sifteo::Random				random;
	random.seed();

	if (cube1 == _mainCube && cube2 == _sideCube)
	{
		mainSide = side1;
		sideSide = side2;
	}
	else if (cube2 == _mainCube && cube1 == _sideCube)
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
	change = true;
    }
    else if (_x >= Map::size)
    {
	_x = Map::size - 1;
	change = true;
    }
    if (_y < 0)
    {
	_y = 0;
	change = true;
    }
    else if (_y >= Map::size)
    {
	_y = Map::size - 1;
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
      _x++;
    if (dir == EDirection::TOP)
      _y++;
    if (dir == EDirection::RIGHT)
      _x--;
    if (dir == EDirection::BOT)
      _y--;
    if (clampPosition() == false)
	swapCubes();
}