#include "Player.hh"

Player::Player(int x, int y) : _x(x), _y(y)
{
    clampPosition();
}

Player::~Player(){}

bool	Player::clampPosition()
{
    bool	change = false;

    if (_x < 0)
    {
	_x = 0;
	change = true;
    }
    else if (_x >= Map::size())
    {
	_x = Map::size() - 1;
	change = true;
    }
    if (_y < 0)
    {
	_y = 0;
	change = true;
    }
    else if (_y >= Map::size())
    {
	_y = Map::size() - 1;
	change = true;
    }
    return (change);
}

void	Player::move(const EDirection &dir)
{
    if (dir == EDirection::LEFT)
      _x--;
    if (dir == EDirection::TOP)
      _y--;
    if (dir == EDirection::RIGHT)
      _x++;
    if (dir == EDirection::BOT)
      _y++;
    clampPosition();
}