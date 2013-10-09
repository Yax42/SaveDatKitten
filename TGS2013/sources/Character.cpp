#include "Character.hh"
#include "Player.hh"

Character::Character(const Sifteo::PinnedAssetImage & image, float x, float y, float maxSpeed) :
	_image(image), _pos(), _goal(), _goalAlive(false), _maxSpeed(maxSpeed)
{
	_pos.set(x, y);
	_goal.set(0, 0);
}

void					Character::update(float delta)
{
	if (_goalAlive == false)
	{
		_spriteId = 0;
		return ;
	}
	Sifteo::Float2		prevDir = _goal - _pos;
	Sifteo::Float2		velocity = (prevDir).normalize() * delta * _maxSpeed;
	_pos += velocity;
	Sifteo::Float2		dir = (_goal - _pos).normalize();
	if ((dir.x < 0) != (prevDir.x < 0) || (dir.y < 0) != (prevDir.y < 0))
	{
		_goalAlive = 0;
		_pos = _goal;
		_spriteId = 0;
		return ;
	}

	int		x = (dir.x < 0.3f && dir.x > -0.3f) ? 0 :
				(dir.x > 0.3f) ? -1 : 1;

	int		y = (dir.y < 0.3f && dir.y > -0.3f) ? 0 :
				(dir.y > 0.3f) ? -1 : 1;

	int		add = (x == 0 && y == -1) ? 0 :
				(x == 1 && y == -1) ? 1 :
				(x == 1 && y == 0) ? 2 :
				(x == 1 && y == 1) ? 3 :
				(x == 0 && y == 1) ? 4 :
				(x == -1 && y == 1) ? 5 :
				(x == -1 && y == 0) ? 6 : 7;
	_spriteId = ((_spriteId + 1) % 4) + add * 4;
}

void				Character::print(Player &player)
{
	unsigned int	x = static_cast<unsigned int> (player.x());
	unsigned int	y = static_cast<unsigned int> (player.y());

	if (x != _pos.x / Sifteo::LCD_width || y != _pos.y / Sifteo::LCD_height)
		return ;
	//.bg0.image(Sifteo::vec((static_cast<int>(_pos.x)) % Sifteo::LCD_width, (static_cast<int>(_pos.y)) % Sifteo::LCD_height), _image, _spriteId);
	player.cube().sprites[5].move((static_cast<int>(_pos.x)) % Sifteo::LCD_width, (static_cast<int>(_pos.y)) % Sifteo::LCD_height);
	player.cube().sprites[5].setImage(_image, _spriteId);
}

void			Character::setGoal(float x, float y)
{
	_goal.set(x, y);
	_goalAlive = true;
}

bool			Character::goalAlive() const
{
	return (_goalAlive);
}