#pragma once

#include "Character.hh"
#include "PlayerCube.hh"

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
    Player(int x, int y, PlayerCube mainCube, PlayerCube sideCube, int id);
    ~Player();
	void						connection(Sifteo::VideoBuffer *cube1, unsigned int side1, Sifteo::VideoBuffer *cube2, unsigned int side2);
    int							x() const { return _x; }
    int							y() const { return _y; }
    int							xOld() const { return _xOld; }
    int							yOld() const { return _yOld; }
    Sifteo::VideoBuffer			&cube() { return *_mainCube.cube(); }
    Sifteo::VideoBuffer			&cubeOld() { return *_sideCube.cube(); }
	SortSprites					&drawer() { return (_mainCube.drawer()); }
	void						update(float delta) { _char.update(delta); }
	void						flush();
	void						print(SortSprites &sprites, unsigned int x, unsigned int y) { _char.print(sprites, x, y); }

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