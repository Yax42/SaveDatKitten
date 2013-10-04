#include "Character.hh"

Character::Character(const Sifte::AssetImage & image, float x, float y, float maxSpeed) :
	_image(image, _pos(x, y), _goal(0, 0), _goalAlive(false), _maxSpeed(maxSpeed)
{
}

void					Character::Update(float delta)
{
	if (_goalAlive == false)
	{
		_spriteId = 0;
		return ;
	}
	Sifteo::Float2		prevDir = _goal - _pos;
	Sifteo::Float2		velocity = (prevDir).normalized() * delta * _maxSpeed;
	_pos += velocity;
	Sifteo::Float2		dir = (_goal - _pos).normalized();
	if ((dir.x < 0) != (prevDir.x < 0) || (dir.y < 0) != (prevDir.y < 0))
	{
		_goalAlive = 0;
		_pos = _goal;
		_spriteId = 0;
		return ;
	}

	int		x = (dir.x < 0.3f && dir.x > -0.3f) ? 0
				(dir.x > 0.3f) ? -1 : 1

	int		y = (dir.y < 0.3f && dir.y > -0.3f) ? 0
				(dir.y > 0.3f) ? -1 : 1

	int		add = (x == 0 && y == -1) ? 0 :
				(x == 1 && y == -1) ? 1 :
				(x == 1 && y == 0) ? 2 :
				(x == 1 && y == 1) ? 3 :
				(x == 0 && y == 1) ? 4 :
				(x == -1 && y == 1) ? 5 :
				(x == -1 && y == 0) ? 6 : 7;
	_spriteId = ((_spriteId + 1) % 4) + add * 4;
}

void			Character::print()
{
}

void			Character::setGoal(const Sifteo::Float2 &newGoal)
{
	_goal = newGoal;
	_goalAlive = true;
}

bool			Character::goalAlive() const
{
	return (_goalAlive);
}