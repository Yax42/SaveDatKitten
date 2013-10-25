#include "SortSprites.hh"
#include "assets.gen.h"


Character	*SortSprites::characters[] = { NULL};//, NULL, NULL };

SortSprites::SortSprites(Sifteo::VideoBuffer &buffer) :
	_cube(&buffer),
	_spriteNbr(0)
{
	for (int i = 0; i < MAX_SPRITES; ++i)
		_toDraw[i].img = NULL;
}

SortSprites::~SortSprites()
{
}

void			SortSprites::setCharacters()
{
	for (int i = 0; i < NB_CHARS; ++i)
	{
		_toDraw[i].img = SortSprites::characters[i]->image();
		_toDraw[i].idx = i;
		++_spriteNbr;
	}
}

void			SortSprites::updateCharacters(int x, int y)
{
	for (int i = 0; i < NB_CHARS; ++i)
	{
		int			newX = SortSprites::characters[i]->x() - x * Sifteo::LCD_width;
		int			newY = SortSprites::characters[i]->y() - y * Sifteo::LCD_height;

		//LOG("x = %d y = %d\n", newX, newY);

		if ( newX < -32 ||
			newX > Sifteo::LCD_width ||
			newY < -32 ||
			newY > Sifteo::LCD_height)
		{
			_cube->sprites[_toDraw[i].idx].setImage(Plants, 35);
		}
		else
		{
			_toDraw[i].frame = SortSprites::characters[i]->frame();
			_toDraw[i].pos.x = newX;
			_toDraw[i].pos.y = newY;
			_cube->sprites[_toDraw[i].idx].move(_toDraw[i].pos.x, _toDraw[i].pos.y);
			_cube->sprites[_toDraw[i].idx].setImage(*(_toDraw[i].img), _toDraw[i].frame);
		}
	}
}

unsigned int	SortSprites::addSprite(unsigned int x,
							   unsigned int y,
							   unsigned int frame,
							   Sifteo::PinnedAssetImage const *img)
{
	if (_spriteNbr >= MAX_SPRITES)
		return 0;
	_toDraw[_spriteNbr].pos.x = x;
	_toDraw[_spriteNbr].pos.y = y;
	_toDraw[_spriteNbr].frame = frame;
	_toDraw[_spriteNbr].img = img;
	_toDraw[_spriteNbr].idx = _spriteNbr;
	++_spriteNbr;
	return (_spriteNbr - 1);
}

void	SortSprites::initSort()
{
	for (int i = 0; i < _spriteNbr; ++i)
		_sorted[i] = &_toDraw[i];
	for (int i = 0; i < _spriteNbr; ++i)
		for (int j = i + 1; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
			{
				SSprite		*tmp;

				tmp = _sorted[i];
				_sorted[i] = _sorted[j];
				_sorted[j] = tmp;

				int			tmp2;
				tmp2 = _sorted[i]->idx;
				_sorted[i]->idx = _sorted[j]->idx;
				_sorted[j]->idx = tmp2;
			}
		}
	for (int i = 0; i < _spriteNbr; ++i)
	{
		_cube->sprites[i].move(_sorted[i]->pos.x, _sorted[i]->pos.y);
		_cube->sprites[i].setImage(*(_sorted[i]->img), _sorted[i]->frame);
	}
	for (unsigned int i = _spriteNbr; i < MAX_SPRITES; ++i)
		_cube->sprites[i].setImage(Plants, 35);
}

void	SortSprites::flush()
{
	for (int i = 0; i < _spriteNbr; ++i)
		for (int j = i + 1; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
			{
				SSprite		*tmp;

				tmp = _sorted[i];
				_sorted[i] = _sorted[j];
				_sorted[j] = tmp;

				int			tmp2;
				tmp2 = _sorted[i]->idx;
				_sorted[i]->idx = _sorted[j]->idx;
				_sorted[j]->idx = tmp2;

				_cube->sprites[i].move(_sorted[i]->pos.x, _sorted[i]->pos.y);
				_cube->sprites[i].setImage(*(_sorted[i]->img), _sorted[i]->frame);
				_cube->sprites[j].move(_sorted[j]->pos.x, _sorted[j]->pos.y);
				_cube->sprites[j].setImage(*(_sorted[j]->img), _sorted[j]->frame);
			}
		}
}

void	SortSprites::clean()
{
	_spriteNbr = NB_CHARS;
}
