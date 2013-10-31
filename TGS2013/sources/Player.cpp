#include "Player.hh"
#include "Map.hh"
#include "assets.gen.h"

#include "Random.hh"

Player::Player(int x, int y, Sifteo::VideoBuffer *mainCube, Sifteo::VideoBuffer *sideCube, int id) :
	_x(x),
	_y(y),
	_xOld(-1),
	_yOld(-1),
	_mainCubeInstance(mainCube),
	_sideCubeInstance(sideCube),
	_mainCube(&_mainCubeInstance),
	_sideCube(&_sideCubeInstance),
	_char(Pikachu, x * Sifteo::LCD_width, y * Sifteo::LCD_height, 150)
{
	SortSprites::characters[id] = &_char;
    clampPosition();
}

Player::~Player(){}

void		Player::connection(Sifteo::VideoBuffer *cube1, unsigned int side1, Sifteo::VideoBuffer *cube2, unsigned int side2)
{
	int		mainSide;
	int		sideSide;

	if (cube1 == _mainCube->cube() && cube2 == _sideCube->cube())
	{
		mainSide = side1;
		sideSide = side2;
	}
	else if (cube2 == _mainCube->cube() && cube1 == _sideCube->cube())
	{
		mainSide = side2;
		sideSide = side1;
	}
	else
		return ;
	//gerrer l'orientation des cubes
	move(mainSide);
	_char.setGoal(_x, _y);
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
    PlayerCube		*tmp = _mainCube;
    _mainCube = _sideCube;
    _sideCube = tmp;
}

void		Player::move(int dir)
{
	int		xOld = _x;
	int		yOld = _y;
	
    if (dir == EDirection::LEFT)
		_x++;
    if (dir == EDirection::TOP)
		_y++;
    if (dir == EDirection::RIGHT)
		_x--;
    if (dir == EDirection::BOT)
		_y--;
    if (clampPosition() == false)
	{
		_yOld = yOld;
		_xOld = xOld;
		swapCubes();
	}

}

void					Player::flush()
{
	_mainCube->drawer().updateCharacters(_x, _y);
    _mainCube->drawer().flush();
	_sideCube->drawer().updateCharacters(_xOld, _yOld);
    _sideCube->drawer().flush();
}

void					Player::updateChar()
{
    _mainCube->drawer().setCharacters();
    _sideCube->drawer().setCharacters();
}