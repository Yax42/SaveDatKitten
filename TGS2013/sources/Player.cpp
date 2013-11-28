#include <sifteo.h>

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
	_char((id == 0) ? Toad : Pikachu, x * Sifteo::LCD_width, y * Sifteo::LCD_height, 150),
	shining(false)
{
    clampPosition();
	_char._isDir = true;
	//_mainCube->cube()->bg1.maskedImage(Paw, Pikachu);// Sifteo::vec(0, 0));
	//_sideCube->cube()->bg1.maskedImage(Paw, Plants);// Sifteo::vec(0, 0));
	//_sideCube->cube()->bg1.maskedImage(Paw, Sifteo::vec(0, 0));
}

Player::~Player(){}

void		Player::move()
{
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

void					Player::flush(Map &map)
{
	//LOG("%f %f\n", _char._dir.x, _char._dir.y);
	Sifteo::Int2 	accel = _mainCube.cube()->physicalAccel().xy();
	///LOG("%d %d\n", accel.x, accel.y);
	if (accel.x > 10 || accel.x < -10)
		_char._dir.x = accel.x;
	else
		_char._dir.x = 0;
	if (accel.y > 10 || accel.y < -10)
		_char._dir.y = accel.y;
	else
		_char._dir.y = 0;

	//_char._dir = accel;

	_mainCube.drawer().updateCharacters(_x, _y);

	int prevX = _x;
	int prevY = _y;
	_x = (_char.x() + 16) / 128;
	_y = (_char.y() + 16) / 128;

	if (_y != prevY || _x != prevX)
	{
		drawer().clean();
		map.printCase(*this);
		drawer().initSort();
	}
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