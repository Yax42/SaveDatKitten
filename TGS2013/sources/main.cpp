/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "assets.gen.h"

#include "SaveKittens.hh"

Sifteo::Random gRandom;

static Sifteo::AssetSlot MainSlot = Sifteo::AssetSlot::allocate()
    .bootstrap(GameAssets);

static Sifteo::Metadata M = Sifteo::Metadata()
    .title("Save the kitten")
    .package("TGS.kitten", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);

void main()
{
	static SaveKittens	kittens;
    Sifteo::TimeStep ts;

    kittens.init();
    while (1)
	{
		kittens.update(ts.delta());
		Sifteo::System::paint();
        ts.next();
    }
}
