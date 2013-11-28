#pragma once

#include "Character.hh"
#include "PlayerCube.hh"

namespace EDirection
{
	enum 	EDirection
	{
		BOT,
		RIGHT,
		TOP,
		LEFT,
		IDLE
	};
};

class Kitty;

class Player
{
public:
    Player(int x, int y, Sifteo::VideoBuffer *mainCube, Sifteo::VideoBuffer *sideCube, int id);
    ~Player();
	void						connection(Sifteo::VideoBuffer *cube1, unsigned int side1, Sifteo::VideoBuffer *cube2, unsigned int side2);
    int							x() const { return _x; }
    int							y() const { return _y; }
    int							xOld() const { return _xOld; }
    int							yOld() const { return _yOld; }
    Sifteo::VideoBuffer			&cube() { return *_mainCube->cube(); }
    Sifteo::VideoBuffer			&cubeOld() { return *_sideCube->cube(); }
	SortSprites					&drawer() { return (_mainCube->drawer()); }
	SortSprites					&secondDrawer() { return (_sideCube->drawer()); }
	void						update(float delta) { _char.update(delta); }
	void						updateChar();
	void						flush();
	void						print(SortSprites &sprites, unsigned int x, unsigned int y) { _char.print(sprites, x, y); }
	void						follow(const Sifteo::PinnedAssetImage &image, const Character &target);
	//void						updatePaw(Kitty &kitty);

private:
    int				_x;
    int				_y;
    int				_xOld;
    int				_yOld;
    PlayerCube		_mainCubeInstance;
    PlayerCube		_sideCubeInstance;
    PlayerCube		*_mainCube;
    PlayerCube		*_sideCube;
	Character		_char;
public:
	bool			shining;

private:
    void	move(int dir);
    void	swapCubes();
    bool	clampPosition();
};