#pragma once

#include QMK_KEYBOARD_H

// Bit patterns for defined layers
#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

enum layer_symbols_t {
	SYM_BASE=0,
	SYM_ADJUST,
	SYM_LOWER,
	SYM_RAISE
};

enum modifier_symbols_t {
	SYM_SHIFT=0,
	SYM_CTRL,
	SYM_ALT,
	SYM_CMD,
	SYM_CAPS
};


void oled_write_layer_row(uint8_t sym, uint8_t row);
void oled_write_mod_row(uint8_t sym, bool set, uint8_t col, uint8_t row);

void oled_render_mod_status(uint8_t col, uint8_t row);
void oled_render_layer_state(uint8_t col, uint8_t row);

void oled_render_boot(void);
void oled_set_reboot(void);

// Used in the mod status method
#ifdef OLED_MOD_NO_GAP
  #define OLED_MOD_STEP_2 2
  #define OLED_MOD_STEP_3 3
#else
  #define OLED_MOD_STEP_2 3 
  #define OLED_MOD_STEP_3 4 
#endif
