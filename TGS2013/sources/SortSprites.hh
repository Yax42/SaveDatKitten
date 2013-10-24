#pragma once

#include <sifteo.h>

#define	MAX_SPRITES		8

class	SortSprites
{
public:
	struct	SSprite
	{
		Sifteo::Int2 					pos;
		unsigned char 					frame;
		Sifteo::PinnedAssetImage const	*img;

		SSprite()
		{
		}

		SSprite(SSprite const &sprite)
		{
			*this = sprite;
		}

		SSprite		&operator=(SSprite const &oth)
		{
			pos = oth.pos;
			frame = oth.frame;
			img = oth.img;
			return (*this);
		}

		bool		operator<(SSprite const &oth)
		{
			return (pos.y < oth.pos.y);
		}

		bool		operator>(SSprite const &oth)
		{
			return (pos.y > oth.pos.y);
		}
	};

private:
	SSprite			_toDraw[MAX_SPRITES];
	SSprite			*_sorted[MAX_SPRITES];
	unsigned int	_spriteNbr;

public:
	SortSprites();
	~SortSprites();

	void	addSprite(SSprite const &sprite);
	void	flush(Sifteo::VideoBuffer &buffer);
};
