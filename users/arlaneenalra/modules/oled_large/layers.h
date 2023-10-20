#pragma once

#include QMK_KEYBOARD_H

enum modifier_symbols_t {
	SYM_SHIFT=0,
	SYM_CTRL,
	SYM_ALT,
	SYM_CMD,
	SYM_CAPS
};

enum layer_symbols_t {
    SYM_BLANK,
    SYM_BASE,
    SYM_LOWER,
    SYM_RAISE,
    SYM_ADJUST,
    SYM_NAV,
    SYM_NUMBER,

    SYM_FROG
};

 

void oled_write_layer_row(uint8_t sym, uint8_t row);
void oled_write_mod_row(uint8_t sym, bool set, uint8_t col, uint8_t row);
void oled_render_big_sym(uint8_t col, uint8_t row, uint8_t sym);

void oled_render_mod_status(uint8_t col, uint8_t row);
void oled_render_layer_state(uint8_t col, uint8_t row);
void oled_render_frog_state(uint8_t col, uint8_t row, bool is_frog);

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
