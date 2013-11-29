#include "SortSprites.hh"
#include "assets.gen.h"


Character	*SortSprites::characters[] = { NULL, NULL};//, NULL };

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
		++_spriteNbr;
	}
}

void			SortSprites::updateCharacters(int x, int y)
{
	for (int i = 0; i < NB_CHARS; ++i)
	{
		int			newX = SortSprites::characters[i]->x() - x * Sifteo::LCD_width;
		int			newY = SortSprites::characters[i]->y() - y * Sifteo::LCD_height;

		if ( newX < -32 ||
			newX > (int) Sifteo::LCD_width ||
			newY < -32 ||
			newY > (int) Sifteo::LCD_height)
		{
			_cube->sprites[_toDraw[i].idx + NB_ABOVE].move(128, 128);
			_cube->sprites[_toDraw[i].idx + NB_ABOVE].setImage(Empty, 0);
		}
		else
		{
			_toDraw[i].frame = SortSprites::characters[i]->frame();
			_toDraw[i].x = newX;
			_toDraw[i].y = newY;
			_cube->sprites[_toDraw[i].idx + NB_ABOVE].move(_toDraw[i].x, _toDraw[i].y);
			_cube->sprites[_toDraw[i].idx + NB_ABOVE].setImage(*(_toDraw[i].img), _toDraw[i].frame);
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
	_toDraw[_spriteNbr].x = x;
	_toDraw[_spriteNbr].y = y;
	_toDraw[_spriteNbr].frame = frame;
	_toDraw[_spriteNbr].img = img;
	_toDraw[_spriteNbr].idx = _spriteNbr;
	++_spriteNbr;
	return (_spriteNbr);
}

void	SortSprites::swap(int i, int j)
{
	SSprite		*tmp;
//	int			tmp2;

	tmp = _sorted[i];
	_sorted[i] = _sorted[j];
	_sorted[j] = tmp;
//	tmp2 = _sorted[i]->idx;
	_sorted[i]->idx = i;
	_sorted[j]->idx = j;
}

void	SortSprites::initSort()
{
	for (int i = 0; i < _spriteNbr; ++i)
	{
		_toDraw[i].idx = i;
		_sorted[i] = &_toDraw[i];
	}
	for (int i = 0; i < _spriteNbr; ++i)
	{
		for (int j = i + 1; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
				swap(i, j);
		}
	}
	for (int i = 0; i < _spriteNbr; ++i)
	{
		_cube->sprites[i + NB_ABOVE].move(_sorted[i]->x, _sorted[i]->y);
		_cube->sprites[i + NB_ABOVE].setImage(*(_sorted[i]->img), _sorted[i]->frame);
	}
	for (unsigned int i = _spriteNbr + NB_ABOVE; i < MAX_SPRITES; ++i)
		_cube->sprites[i].setImage(Empty, 0);
}

void	SortSprites::flush()
{
	for (int i = 0; i < _spriteNbr; ++i)
	{
		for (int j = i + 1; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
			{
				swap(i, j);

				_cube->sprites[i + NB_ABOVE].move(_sorted[i]->x, _sorted[i]->y);
				_cube->sprites[i + NB_ABOVE].setImage(*(_sorted[i]->img), _sorted[i]->frame);
				_cube->sprites[j + NB_ABOVE].move(_sorted[j]->x, _sorted[j]->y);
				_cube->sprites[j + NB_ABOVE].setImage(*(_sorted[j]->img), _sorted[j]->frame);
			}
		}
	}
}

void	SortSprites::clean()
{
	_spriteNbr = NB_CHARS;
}

void		SortSprites::addChar(Character *c)
{
	static int id = 0;
	characters[id++] = c;
}