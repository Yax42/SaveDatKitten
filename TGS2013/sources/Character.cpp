#include "Character.hh"
#include "Player.hh"
#include "SortSprites.hh"
#include "Map.hh"

#include "Random.hh"

Character::Character(const Sifteo::PinnedAssetImage & image, int x, int y, float maxSpeed) :
	_image(image), _pos(), _goal(), _goalAlive(false), _maxSpeed(maxSpeed), _speed(0)
{
	
	SortSprites::addChar(this);
	_pos.set(x, y);
	//LOG("%f\n", x);
	_goal.set(0, 0);
	_isDir = false;
	_dir.x = 0;
	_dir.y = 0;
	
}

void					Character::update(float delta)
{
	Sifteo::Float2		dir;
	if (_dir.x == 0 && _dir.y == 0)
	{
	}
	else if (_isDir)
	{
		Sifteo::Float2		prevPos = _pos;
		Sifteo::Float2		velocity = (_dir).normalize() * delta * _speed;
		_pos += velocity;
		dir = (_dir).normalize();
		if (_pos.x < 16 || _pos.x > MAP_SIZE * 128 - 16 - 32)
			_pos.x = prevPos.x;
		if (_pos.y < 16 - 32 || _pos.x > MAP_SIZE * 128 - 16 - 32)
			_pos.x = prevPos.y;
	}
	else
	{
		if (_goalAlive == false)
		{
			if (static_cast<unsigned int>(gRandom.random() * 2))
			{
				_spriteId = 1;
				return ;
			}
			else
				setGoal(static_cast<int>(_goal.x / Sifteo::LCD_height), static_cast<int>(_goal.y / Sifteo::LCD_width), _maxSpeed / 4);
		}
		Sifteo::Float2		prevDir = _goal - _pos;
		Sifteo::Float2		velocity = (prevDir).normalize() * delta * _speed;
		_pos += velocity;
		Sifteo::Float2		dir = (_goal - _pos).normalize();
		if ((dir.x < 0) != (prevDir.x < 0) || (dir.y < 0) != (prevDir.y < 0))
		{
			_goalAlive = 0;
			_pos = _goal;
			_spriteId = 0;
			return ;
		}
	}

	int		x = (dir.x < 0.5f && dir.x > -0.5f) ? 0 :
				(dir.x > 0.5f) ? -1 : 1;

	int		y = (dir.y < 0.5f && dir.y > -0.5f) ? 0 :
				(dir.y > 0.5f) ? -1 : 1;

	int		add = (dir.x > 0.5f) ? 1 :
				(dir.y < -0.5f) ? 2 :
				(dir.x < -0.5f) ? 3 : 0;

	_spriteId = ((_spriteId + 1) % 4) + add * 4;
}

void				Character::print(SortSprites &sprites, unsigned int x, unsigned int y)
{
	if (x != static_cast<unsigned int>(_pos.x / Sifteo::LCD_width) || y != static_cast<unsigned int>(_pos.y / Sifteo::LCD_height))
		return ;
	sprites.addSprite((static_cast<unsigned int>(_pos.x)) % Sifteo::LCD_width,
				(static_cast<unsigned int>(_pos.y)) % Sifteo::LCD_height,
				_spriteId, &_image);
	//.bg0.image(Sifteo::vec((static_cast<int>(_pos.x)) % Sifteo::LCD_width, (static_cast<int>(_pos.y)) % Sifteo::LCD_height), _image, _spriteId);
	//player.cube().sprites[5].move((static_cast<int>(_pos.x)) % Sifteo::LCD_width, (static_cast<int>(_pos.y)) % Sifteo::LCD_height);
	//player.cube().sprites[5].setImage(_image, _spriteId);
}

void			Character::setGoal(float x, float y, float speed)
{
	_goal.set(x * Sifteo::LCD_width + 16 + static_cast<unsigned int>(gRandom.random() * 64),
				y * Sifteo::LCD_height + 16 + static_cast<unsigned int>(gRandom.random() * 64));
	_goalAlive = true;
	if (speed < 0)
		speed = _maxSpeed;
	_speed = speed;
}

bool			Character::goalAlive() const
{
	return (_goalAlive);
}