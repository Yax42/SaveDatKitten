APP = SaveTheKitten

include $(SDK_DIR)/Makefile.defs

OBJS = $(ASSETS).gen.o sources/Map.o sources/Player.o sources/SaveKittens.o sources/main.o sources/Character.o sources/SortSprites.o sources/PlayerCube.o
ASSETDEPS += resources/*.png $(ASSETS).lua

# build assets.html to proof stir-processed assets.
# comment out to disable.
ASSETS_BUILD_PROOF := yes

include $(SDK_DIR)/Makefile.rules
