#include "SortSprites.hh"
#include "assets.gen.h"

SortSprites::SortSprites() :
	_spriteNbr(0)
{
	for (int i = 0; i < MAX_SPRITES; ++i)
		_toDraw[i].img = NULL;
}

SortSprites::~SortSprites()
{
}

void	SortSprites::addSprite(unsigned int x,
							   unsigned int y,
							   unsigned int frame,
							   Sifteo::PinnedAssetImage const *img)
{
	if (_spriteNbr == MAX_SPRITES)
		return;
	_toDraw[_spriteNbr].pos.x = x;
	_toDraw[_spriteNbr].pos.y = y;
	_toDraw[_spriteNbr].frame = frame;
	_toDraw[_spriteNbr].img = img;
	++_spriteNbr;
}

void	SortSprites::flush(Sifteo::VideoBuffer &buffer)
{
	LOG("sprites nbr = %d\n", _spriteNbr);
	for (unsigned int i = 0; i < MAX_SPRITES; ++i)
		buffer.sprites[i].setImage(Plants, 35);
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
	for (int i = 0; i < _spriteNbr; ++i)
	{
		buffer.sprites[i].move(_sorted[i]->pos.x, _sorted[i]->pos.y);
		buffer.sprites[i].setImage(*_sorted[i]->img, _sorted[i]->frame);
	}
	_spriteNbr = 0;
}
