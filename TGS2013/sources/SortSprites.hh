#pragma once

#include <sifteo.h>

#include "Character.hh"

#define	MAX_SPRITES		8
#define NB_CHARS		1

class	SortSprites
{
public:
	struct	SSprite
	{
		unsigned int					x, y;
		Sifteo::Int2 					pos;
		unsigned char 					frame;
		Sifteo::PinnedAssetImage const	*img;
		int								idx;

		SSprite() { }

		bool		operator<(SSprite const &oth) { return (y + img->pixelHeight() < oth.y + oth.img->pixelHeight()); }

		bool		operator>(SSprite const &oth) { return (y + img->pixelHeight() > oth.y + oth.img->pixelHeight()); }
	};

	static Character			*characters[NB_CHARS];

private:
	Sifteo::VideoBuffer			*_cube;
	SSprite						_toDraw[MAX_SPRITES];
	SSprite						*_sorted[MAX_SPRITES];
	unsigned int				_spriteNbr;

	void						swap(int i, int j);

public:
	SortSprites(Sifteo::VideoBuffer &buffer);
	~SortSprites();

	void			setCharacters();
	void			updateCharacters(int x, int y);
	SSprite			&getById(unsigned int id) { return (_toDraw[id]); }
	unsigned int	addSprite(unsigned int x, unsigned int y, unsigned int frame, Sifteo::PinnedAssetImage const *img);
	void			initSort();
	void			flush();

	void			clean();
};