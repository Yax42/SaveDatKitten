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
		LEFT
	};
};

class Kitty;

class Player
{
public:
    Player(int x, int y, Sifteo::VideoBuffer *mainCube, int id);
    ~Player();
	void						move();
    int							x() const { return _x; }
    int							y() const { return _y; }
    int							xOld() const { return _xOld; }
    int							yOld() const { return _yOld; }
    Sifteo::VideoBuffer			&cube() { return *_mainCube.cube(); }
	SortSprites					&drawer() { return (_mainCube.drawer()); }
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
    PlayerCube		_mainCube;
	Character		_char;
public:
	bool			shining;

private:
    //void	move(int dir);
    bool	clampPosition();
};