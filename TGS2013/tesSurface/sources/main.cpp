/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>

#include "assets.gen.h"


static Sifteo::AssetSlot MainSlot = Sifteo::AssetSlot::allocate()
    .bootstrap(GameAssets);


static Sifteo::Metadata M = Sifteo::Metadata()
    .title("Tag test")
    .package("TGS.tagTest", "1.0")
    .cubeRange(1);

void main()
{
	Sifteo::VideoBuffer cube;
    Sifteo::TimeStep ts;

    cube.initMode(Sifteo::FB64);
	cube.bg0.image(Sifteo::vec(0, 0), Tag1);
	cube.sprites[0].setImage(Tag1, 0);
    cube.colormap[0] = 0xdddddd;
    cube.colormap[1] = 0x000088;
    while (1)
	{
		//update(ts.delta());
		Sifteo::System::paint();
        ts.next();
    }
}
 /*

#include <sifteo.h>
using namespace Sifteo;

#include "assets.gen.h"


static Sifteo::AssetSlot MainSlot = Sifteo::AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("Accelerometer Chart")
    .package("com.sifteo.extras.accelchart", "0.1")
    .cubeRange(1);

void main()
{
    static VideoBuffer vid;
    static MotionBuffer<256> buf;
    MotionIterator iter(buf);

    buf.attach(0);
    vid.attach(0);
    vid.initMode(FB64);
    //vid.colormap[0] = 0xdddddd;
    //vid.colormap[1] = 0x000088;
	vid.bg0.image(Sifteo::vec(0, 0), Tag1);

    int y = 0;
    int prevX = 32;
    const unsigned ticksPerPixel = 50;

    while (1) {

        while (iter.next()) {
            while (iter.ticks() >= ticksPerPixel) {
                iter.adjustTicks(-ticksPerPixel);

                int x = clamp(32 + iter.accel().x / 2, 0, 63);

                // Draw a line from old X to new X
                int x1 = MIN(x, prevX+1);
                int x2 = MAX(x, prevX-1);
                //vid.fb64.span(vec(x1,y), x2-x1+1, 1);
                prevX = x;

                // Erase one row ahead
                if (++y == 64) y = 0;
                //vid.fb64.span(vec(0,y), 64, 0);
            }
        }

        System::paint();
    }
}
*/