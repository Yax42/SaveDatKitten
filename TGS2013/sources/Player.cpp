#include "Player.hh"
#include "Map.hh"

Player::Player(int x, int y, int currentCubeID, int otherCubeID) : _x(x), _y(y),
	_currentCubeID(currentCubeID), _otherCubeID(otherCubeID)
{
    clampPosition();
}

Player::~Player(){}

void		Player::connection(unsigned int cube1ID, unsigned int side1, unsigned int cube2ID, unsigned int side2)
{
  int		side;

  if (cube1ID == _currentCubeID && cube2ID == _otherCubeID)
	side = side1;
  else if (cube2ID == _currentCubeID && cube1ID == _otherCubeID)
	side = side2;
  else
	return ;
  //move(static_cast<EDirection>(side));
  move(side);
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
    int		tmp = _currentCubeID;
    _currentCubeID = _otherCubeID;
    _otherCubeID = tmp;
}

void		Player::move(int dir)
{
    if (dir == EDirection::LEFT)
      _x--;
    if (dir == EDirection::TOP)
      _y--;
    if (dir == EDirection::RIGHT)
      _x++;
    if (dir == EDirection::BOT)
      _y++;
    if (clampPosition() == false)
	swapCubes();
}