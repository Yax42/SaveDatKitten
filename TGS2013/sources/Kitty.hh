#pragma once

#include <sifteo.h>

#include "Character.hh"

class Kitty
{
public:
	Kitty();
	~Kitty() {};
	Character	&character() { return (_character); }
	void		update(float delta);

private:
	Character	_character;
};