
# Setup OLED files
ifeq ($(OLED_ENABLE),yes)


ifeq ($(OLED_ANIMATIONS),yes)
CFLAGS += -DOLED_ANIMATIONS
SRC += modules/animations/animation-utils.c

ifeq ($(OLED_ANIMATIONS_CRAB),yes)
SRC += modules/animations/crab.c
CFLAGS += -DOLED_ANIMATIONS_CRAB
endif

ifeq ($(OLED_ANIMATIONS_DEMON),yes)
SRC += modules/animations/demon.c
CFLAGS += -DOLED_ANIMATIONS_DEMON
endif

ifeq ($(OLED_ANIMATIONS_MUSIC),yes)
SRC += modules/animations/music-bars.c
CFLAGS += -DOLED_ANIMATIONS_MUSIC
endif

endif

endif
