#include "Player.hh"
#include "Map.hh"
#include "Kitty.hh"
#include "assets.gen.h"

#include "Random.hh"

Player::Player(int x, int y, Sifteo::VideoBuffer *mainCube, int id) :
	_x(x),
	_y(y),
	_xOld(-1),
	_yOld(-1),
	_mainCube(mainCube),
	_char(Toad, x * Sifteo::LCD_width, y * Sifteo::LCD_height, 150),
	shining(true)
{
    clampPosition();
	_char._isDir = true;
	//_mainCube->cube()->bg1.maskedImage(Paw, Pikachu);// Sifteo::vec(0, 0));
	//_sideCube->cube()->bg1.maskedImage(Paw, Plants);// Sifteo::vec(0, 0));
	//_sideCube->cube()->bg1.maskedImage(Paw, Sifteo::vec(0, 0));
}

Player::~Player(){}

/*
void		Player::connection(Sifteo::VideoBuffer *cube1, unsigned int side1, Sifteo::VideoBuffer *cube2, unsigned int side2)
{
	int		mainSide;

	if (cube1 == _mainCube->cube())
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
*/

void		Player::move()
{
	Sifteo::Int2 	accel = _mainCube.cube()->physicalAccel().xy();
	_char._dir = accel;
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

void					Player::flush()
{
	_mainCube.drawer().updateCharacters(_x, _y);
    _mainCube.drawer().flush();
}

void					Player::updateChar()
{
    _mainCube.drawer().setCharacters();
}

void					Player::follow(const Sifteo::PinnedAssetImage &image, const Character &target)
{
	static int		halfScreen = SCREEN_SIZE / 2 - 16;
	int				xCKitty = (target.x() - 16) /  SCREEN_SIZE;
	int				yCKitty = (target.y() - 16) /  SCREEN_SIZE;

	if (xCKitty != x() || yCKitty != y())
	{
		int		xPThis = x() * SCREEN_SIZE + halfScreen;
		int		yPThis = y() * SCREEN_SIZE + halfScreen;
		int		xRKitty = target.x() - xPThis;
		int		yRKitty = target.y() - yPThis;
		if (yRKitty == 0)
			yRKitty = 1;
		if (xRKitty == 0)
			xRKitty = 1;

		int		x = 0;
		int		y = 0;
		int		xSign = (xRKitty > 0) ? 1 : -1;
		int		ySign = (yRKitty > 0) ? 1 : -1;

		if (xSign * xRKitty > ySign * yRKitty)
		{
			x = (xSign > 0) ? SCREEN_SIZE - 32 : 0;
			y = (halfScreen * yRKitty) / (xRKitty * xSign);
			y = y + halfScreen;
		}
		else
		{
			y = (ySign > 0) ? SCREEN_SIZE - 32 : 0;
			x = (halfScreen * xRKitty) / (yRKitty * ySign);
			x = x + halfScreen;
		}

		cube().sprites[0].move(x, y);
		cube().sprites[0].setImage(image, 0);
	}
	else
		cube().sprites[0].setImage(Empty, 0);
}

/*
void					Player::updatePaw(Kitty &kitty)
{
	static int		halfScreen = SCREEN_SIZE / 2 - 16;
	int				xCKitty = kitty.character().x() /  SCREEN_SIZE;
	int				yCKitty = kitty.character().y() /  SCREEN_SIZE;

	if (_shining && (xCKitty != x() || yCKitty != y()))
	{
		int		xPThis = x() * SCREEN_SIZE + halfScreen;
		int		yPThis = y() * SCREEN_SIZE + halfScreen;
		int		xRKitty = kitty.character().x() - xPThis;
		int		yRKitty = kitty.character().y() - yPThis;
		//int		xRKitty = _char.x() - xPThis;
		//int		yRKitty = _char.y() - yPThis;
		if (yRKitty == 0)
			yRKitty = 1;
		if (xRKitty == 0)
			xRKitty = 1;

		int		x = 0;
		int		y = 0;
		int		xSign = (xRKitty > 0) ? 1 : -1;
		int		ySign = (yRKitty > 0) ? 1 : -1;

		if (xSign * xRKitty > ySign * yRKitty)
		{
			x = (xSign > 0) ? SCREEN_SIZE - 32 : 0;
			y = (halfScreen * yRKitty) / (xRKitty * xSign);
			y = y + halfScreen;
		}
		else
		{
			y = (ySign > 0) ? SCREEN_SIZE - 32 : 0;
			x = (halfScreen * xRKitty) / (yRKitty * ySign);
			x = x + halfScreen;
		}

		cube().sprites[0].move(x, y);
		cube().sprites[0].setImage(Paw, 0);
	}
	else
		cube().sprites[0].setImage(Empty, 0);
	_sideCube->cube()->sprites[0].setImage(Empty, 0);

	//cube().bg1.setPanning(Sifteo::vec(0, _y));
}
*/