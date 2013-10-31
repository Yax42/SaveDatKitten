/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include "assets.gen.h"

#include "SaveKittens.hh"

static Sifteo::AssetSlot MainSlot = Sifteo::AssetSlot::allocate()
    .bootstrap(GameAssets);

static Sifteo::Metadata M = Sifteo::Metadata()
    .title("Save the kitten")
    .package("TGS.kitten", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);

Sifteo::Random			gRandom;

void main()
{
	static SaveKittens	kittens;
    Sifteo::TimeStep ts;

	gRandom.seed(42);
    kittens.init();
    while (1)
	{
		kittens.update(ts.delta());
		Sifteo::System::paint();
        ts.next();
    }
}
