#pragma once

#include QMK_KEYBOARD_H 

void oled_render_anim_frame(const char **fast_frames, const char **slow_frames, uint8_t frames_len);
void oled_render_wpm(void);


void oled_render_anim(void);

#ifdef OLED_ANIMATIONS_CRAB
#define ANIM_SCROLL true
#define ANIM_FRAME_WIDTH 72
#define ANIM_SIZE 288
#define ANIM_BOUNCE true
#endif

#ifdef OLED_ANIMATIONS_DEMON
#define ANIM_SCROLL true
#define ANIM_FRAME_WIDTH 32
#define ANIM_SIZE 144
#endif

#ifdef OLED_ANIMATIONS_MUSIC
#define ANIM_SIZE 512
#define ANIM_FRAME 300
#endif


