#include "SortSprites.hh"
#include "assets.gen.h"


Character	*SortSprites::characters[] = { NULL, NULL, NULL };

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
	++_spriteNbr;
	return (_spriteNbr - 1);
}

void	SortSprites::initSort()
{
	for (unsigned int i = 0; i < MAX_SPRITES; ++i)
		_cube->sprites[i].setImage(Plants, 35);
	for (int i = 0; i < _spriteNbr; ++i)
		_sorted[i] = &_toDraw[i];
	for (int i = 0; i < _spriteNbr; ++i)
		for (int j = i; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
			{
				SSprite		*tmp;

				tmp = _sorted[i];
				_sorted[i] = _sorted[j];
				_sorted[j] = tmp;
			}
		}
	for (int i = 0; i < MAX_SPRITES; ++i)
	{
		_cube->sprites[i].move(_sorted[i]->pos.x, _sorted[i]->pos.y);
		_cube->sprites[i].setImage(*_sorted[i]->img, _sorted[i]->frame);
	}
}

void	SortSprites::flush()
{
	bool		hasMoved = false;

	for (int i = 0; i < _spriteNbr; ++i)
		for (int j = i; j < _spriteNbr; ++j)
		{
			if (*_sorted[i] < *_sorted[j])
			{
				SSprite		*tmp;

				tmp = _sorted[i];
				_sorted[i] = _sorted[j];
				_sorted[j] = tmp;
				_cube->sprites[i].move(_sorted[i]->pos.x, _sorted[i]->pos.y);
				_cube->sprites[i].setImage(*_sorted[i]->img, _sorted[i]->frame);
				_cube->sprites[j].move(_sorted[j]->pos.x, _sorted[j]->pos.y);
				_cube->sprites[j].setImage(*_sorted[j]->img, _sorted[j]->frame);
			}
		}
}

void	SortSprites::clean(unsigned int keep)
{
	_spriteNbr = keep;
}
