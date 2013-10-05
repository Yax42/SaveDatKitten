#pragma once

#include "Character.hh"
typedef Sifteo::VideoBuffer *PlayerCube;

namespace EDirection
{
	enum
	{
		BOT,
		RIGHT,
		TOP,
		LEFT
	};
};

class Player
{
public:
    Player(int x, int y, PlayerCube mainCube, PlayerCube sideCube);
    ~Player();
    void						connection(PlayerCube cube1, unsigned int side1, PlayerCube cube2, unsigned int side2);
    int							x() const { return _x; }
    int							y() const { return _y; }
    Sifteo::VideoBuffer			&cube() const { return *_mainCube; }
	void						print(Player &player);

private:
    int				_x;
    int				_y;
    PlayerCube		_mainCube;
    PlayerCube		_sideCube;
	Character		_char;

    void	move(int dir);
    void	swapCubes();
    bool	clampPosition();
};