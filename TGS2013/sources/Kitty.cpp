#include "Kitty.hh"
#include "Random.hh"
#include "Map.hh"
#include "assets.gen.h"

//Kitty::Kitty() : _character(Pikachu, gRandom.random() * MAP_SIZE * SCREEN_SIZE, gRandom.random() * MAP_SIZE * SCREEN_SIZE, 50)
Kitty::Kitty() : _character(Cat, 0, 0, 50)
{
	_character.setGoal(gRandom.raw() % MAP_SIZE, gRandom.raw() % MAP_SIZE);
}

void	Kitty::update(float delta)
{
	if (_character.goalAlive() == false)
		_character.setGoal(gRandom.raw() % MAP_SIZE, gRandom.raw() % MAP_SIZE);
	_character.update(delta);
}