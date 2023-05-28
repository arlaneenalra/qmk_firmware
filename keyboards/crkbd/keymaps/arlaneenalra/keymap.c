/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 Chris Salch <@arlaneenalra>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HME_SCLN RCTL_T(KC_SCLN)

enum custom_keycodes {
  QMK_CUT = SAFE_RANGE,
  QMK_CPY,
  QMK_PSTE,
  QMK_UNDO,

  QMK_LNCH,
  QMK_PMKN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CW_TOGG,  HOME_A,  HOME_S,  HOME_D,  HOME_F,    KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L,HME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_INS,   TT(1),  KC_SPC,     KC_SPC,   TT(2),  KC_DEL 
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_MCTL,                      KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,QMK_UNDO, QMK_CUT, QMK_CPY,QMK_PSTE, KC_LPAD,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   MO(3), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX,QMK_LNCH,QMK_PMKN,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,  KC_GRV, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   MO(3), _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, QK_BOOT,  QK_RBT, QK_MAKE, KC_BRID, KC_BRIU,                      KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute

#ifdef OLED_ANIMATIONS
  #ifdef OLED_ANIMATION_CRAB
    #include "modules/animations/crab.c"
  #endif

  #ifdef OLED_ANIMATION_DEMON
    #include "modules/animations/demon.c"
  #endif

  #ifdef OLED_ANIMATION_BARS
    #include "modules/animations/music-bars.c"
  #endif

  #include "modules/animations/animation-utils.c"
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  } 
  
  return OLED_ROTATION_270;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

#define SYM_BASE 0
#define SYM_ADJUST 1 
#define SYM_LOWER 2
#define SYM_RAISE 3

static const char PROGMEM layer_symbols[][5] = {
 { 0x33, 0xCC, 0x33, 0xCC, 0x33 }, // Base
 { 0x14, 0x22, 0x7F, 0x22, 0x14 }, // Adjust 
 { 0x10, 0x20, 0x7F, 0x20, 0x10 }, // Lower
 { 0x04, 0x02, 0x7F, 0x02, 0x04 }  // Raise
};

#define SYM_SHIFT 0
#define SYM_CTRL 1
#define SYM_ALT 2
#define SYM_CMD 3
#define SYM_CAPS 4

static const char PROGMEM mod_symbols[][6] = {
 { 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C }, // shift 
 { 0x04, 0x02, 0x01, 0x01, 0x02, 0x04 }, // ctl
 { 0x03, 0x07, 0x0C, 0x18, 0x71, 0x61 }, // alt
 { 0x33, 0x2D, 0x12, 0x12, 0x2D, 0x33 }, // cmd
 { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }  // caps word
};


char pixel_buffer[32];

void oled_write_layer_row(uint8_t sym, uint8_t row) {
  uint8_t offset = row * 2;
  uint8_t mask = 0x03 << offset;

  uint8_t val = 0;
  int8_t last_step = -1;

  pixel_buffer[0] = 0;
  pixel_buffer[31] = 0;
  for(int8_t i = 0; i < 30 ; i ++) {
    int8_t step = i / 6;
    if (step != last_step) {
      val = (pgm_read_byte(&layer_symbols[sym][step]) & mask) >> offset;
    }

    pixel_buffer[i + 1] =
      ( val & 0x01 ? 0x0f : 0x00 ) |
      ( val & 0x02 ? 0xf0 : 0x00 );
  }

  oled_write_raw(pixel_buffer, 32);
}

void oled_write_mod_row(uint8_t sym, bool set, uint8_t col, uint8_t row) {
  uint8_t offset = row * 4;
  uint8_t mask = 0x0F << offset;

  uint8_t val = 0;
  int8_t last_step = -1;

  for(int8_t i = 0; i < 12 ; i ++) {
    int8_t step = i / 2;
    if (step != last_step) {
      val = (pgm_read_byte(&mod_symbols[sym][step]) & mask) >> offset;
    }
  
    val = set ? ~val : val;

    pixel_buffer[i + 2 + (col * 18)] =
      ( val & 0x01 ? 0x03 : 0x00 ) |
      ( val & 0x02 ? 0x0C : 0x00 ) | 
      ( val & 0x04 ? 0x30 : 0x00 ) |
      ( val & 0x08 ? 0xC0 : 0x00 );
  }

}

void oled_render_layer_state(void) {
    uint8_t sym = 0;

    switch (layer_state) {
        case L_BASE:
            sym = SYM_BASE;
            break;
        case L_LOWER:
            sym = SYM_LOWER;
            break;
        case L_RAISE:
            sym = SYM_RAISE;
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            sym = SYM_ADJUST;
            break;
    }

    oled_set_cursor(0, 1);
    oled_write_layer_row(sym, 0);
    oled_set_cursor(0, 2);
    oled_write_layer_row(sym, 1);
    oled_set_cursor(0, 3);
    oled_write_layer_row(sym, 2);
    oled_set_cursor(0, 4);
    oled_write_layer_row(sym, 3);
}

void oled_render_mod_status(void) {
  const char blank[] = { 0x0 };

  const uint8_t mod_status = get_mods() | get_oneshot_mods() | get_weak_mods();
  const uint8_t shift_symbol = is_caps_word_on() ? SYM_CAPS : SYM_SHIFT;

  pixel_buffer[0] = 0;
  pixel_buffer[1] = 0;

  pixel_buffer[14] = 0;
  pixel_buffer[15] = 0;
  pixel_buffer[16] = 0;
  pixel_buffer[17] = 0;
  pixel_buffer[18] = 0;
  pixel_buffer[19] = 0;

  pixel_buffer[30] = 0;
  pixel_buffer[31] = 0;

  // Special handling for Caps Word

  oled_set_cursor(0, 11); 
  oled_write_mod_row(
      shift_symbol, mod_status & MOD_MASK_SHIFT, 0, 0);
  oled_write_mod_row(
      SYM_CTRL, mod_status & MOD_MASK_CTRL, 1, 0);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(0, 12);
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      shift_symbol, mod_status & MOD_MASK_SHIFT, 0, 1);
  oled_write_mod_row(
      SYM_CTRL, mod_status & MOD_MASK_CTRL, 1, 1);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(0, 14);
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      SYM_ALT, mod_status & MOD_MASK_ALT, 0, 0);
  oled_write_mod_row(
      SYM_CMD, mod_status & MOD_MASK_GUI, 1, 0);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(0, 15); 
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      SYM_ALT, mod_status & MOD_MASK_ALT, 0, 1);
  oled_write_mod_row(
      SYM_CMD, mod_status & MOD_MASK_GUI, 1, 1);
  
  oled_write_raw(pixel_buffer, 32);
}

char keylog_str[32] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "Key:\n%dx%d,\nk%2d:%c\n",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_set_cursor(0, 6);
    oled_write(keylog_str, false);
}

#ifndef OLED_ANIMATIONS
void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}
#endif

void oled_render_boot(void) {
  oled_clear();
  for (int i = 0; i < 16; i++) {
    oled_set_cursor(0, i);
    oled_write_P(PSTR("BOOT "), false);
  }

  oled_render_dirty(true);
} 

bool oled_task_user(void) {
  if (is_keyboard_master()) {
      oled_render_layer_state();
      oled_render_keylog();
      oled_render_mod_status();
  } else {
    #ifndef OLED_ANIMATIONS
    oled_render_logo();
    #else
    oled_render_anim();
    #endif
  }
  return false;
}

bool reboot = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  
    switch(keycode) {
      case QK_BOOT:
        // Display a special logo prior to rebooting...
        reboot = true;
        break;

      case QMK_CPY:
        SEND_STRING(SS_LGUI("c"));
        break;

       case QMK_CUT:
        SEND_STRING(SS_LGUI("x"));
        break;

       case QMK_PSTE:
        SEND_STRING(SS_LGUI("v"));
        break;

       case QMK_UNDO:
        SEND_STRING(SS_LGUI("z"));
        break;

       case QMK_LNCH:
        SEND_STRING("/giphy lunch");
        break;

       case QMK_PMKN:
        SEND_STRING("/giphy pumpkin");
        break;
    }
  }

  return true;
}

void shutdown_user(void) {
  if (reboot) {
    oled_render_boot();
  }
}

#endif // OLED_ENABLE
