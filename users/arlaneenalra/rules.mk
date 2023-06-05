CAPS_WORD_ENABLE = yes


SRC += core.c

# Setup OLED files
ifeq ($(OLED_ENABLE),yes)

OLED_LAYER = yes

ifeq ($(OLED_ANIMATIONS),yes)
# This implies wpm
WPM_ENABLE = yes

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

# Special rendering code

ifeq ($(OLED_LAYER),yes)
SRC += modules/oled_large/layer_render.c modules/oled_large/reboot.c
endif

endif

