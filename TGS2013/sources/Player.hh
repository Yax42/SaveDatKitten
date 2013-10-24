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
    int							xOld() const { return _xOld; }
    int							yOld() const { return _yOld; }
    Sifteo::VideoBuffer			&cube() const { return *_mainCube; }
	void						print(Player &player) { _char.print(player); }
	void						update(float delta) { _char.update(delta); }
	void						print(SortSprites &sprites, Sifteo::VideoBuffer *cube, unsigned int x, unsigned int y) { _char.print(sprites, cube, x, y); }

private:
    int				_x;
    int				_y;
    int				_xOld;
    int				_yOld;
    PlayerCube		_mainCube;
    PlayerCube		_sideCube;
	Character		_char;

    void	move(int dir);
    void	swapCubes();
    bool	clampPosition();
};