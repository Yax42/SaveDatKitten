APP = SaveTheKitten

include $(SDK_DIR)/Makefile.defs

OBJS = $(ASSETS).gen.o sources/main.o
ASSETDEPS += resources/*.png $(ASSETS).lua

# build assets.html to proof stir-processed assets.
# comment out to disable.
ASSETS_BUILD_PROOF := yes

include $(SDK_DIR)/Makefile.rules
