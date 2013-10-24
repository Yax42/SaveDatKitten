#pragma once

#include <sifteo.h>

#include "Character.hh"

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

		bool		operator<(SSprite const &oth)
		{
			return (pos.y < oth.pos.y);
		}

		bool		operator>(SSprite const &oth)
		{
			return (pos.y > oth.pos.y);
		}
	};

	static Character			*characters[3];

private:
	Sifteo::VideoBuffer			&_cube;
	SSprite						_toDraw[MAX_SPRITES];
	SSprite						*_sorted[MAX_SPRITES];
	unsigned int				_spriteNbr;

	SortSprites();

public:
	SortSprites(Sifteo::VideoBuffer &buffer);
	~SortSprites();

	SSprite			&getById(unsigned int id) { return (_toDraw[id]); }
	unsigned int	addSprite(unsigned int x, unsigned int y, unsigned int frame, Sifteo::PinnedAssetImage const *img);
	void			initSort();
	void			flush();

	void			clean(unsigned int keep = 3);
};
