/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

static const unsigned int gNumCubes = 3;
Random gRandom;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("Save the kitten")
    .package("TGS.kitten", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);

class SaveKittens
{
private:   
    VideoBuffer vid[gNumCubes];

public:

    void init()
    {
		for (int i = 0; i < gNumCubes; ++i)
		{
	        vid[i].initMode(BG0_SPR_BG1);
	        vid[i].attach(i);
	        vid[i].bg0.image(vec(0,0), Background);
		}
		Events::neighborAdd.set(&SaveKittens::onNeighborAdd, this);
	}

	void update(TimeDelta dt)
	{
	}

	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
	{
		for (int i = 0; i < gNumCubes; ++i)
	        vid[i].bg1.image(vec(-20,0), Toto);
	}
};

void main()
{
	static SaveKittens	kittens;

    kittens.init();
    
    TimeStep ts;
    while (1)
	{
		kittens.update(ts.delta());
		System::paint();
        ts.next();
    }
}
