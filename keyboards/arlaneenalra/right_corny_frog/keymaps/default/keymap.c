// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>

#include <arlaneenalra.h>

enum frog_layers {
  _FROG_BASE,
  _GREEN_BASE,
  _FROG_NUMBER,
  _GREEN_NUMBER,
  _SYMBOL,
  _GREEN_SYMBOL,
  _ORANGE,
  _ORANGE_SYMBOL
};

const uint8_t PROGMEM layer_render_map[] = {
 [_FROG_BASE] = SYM_BASE,
 [_GREEN_BASE] = SYM_LOWER,

 [_FROG_NUMBER] = SYM_NUMBER,
 [_GREEN_NUMBER] = SYM_LOWER,
 
 [_SYMBOL] = SYM_ADJUST,
 [_GREEN_SYMBOL] = SYM_LOWER,

 [_ORANGE] = SYM_NAV,
 [_ORANGE_SYMBOL] = SYM_FROG,
};

enum frog_keys {
  FRK_NU = ARL_SAFE,
  FRK_SY,
};

#define GRN_BS LT(_GREEN_BASE, KC_SPC)
#define GRN_NU LT(_GREEN_NUMBER, KC_SPC)
#define GRN_SY LT(_GREEN_SYMBOL, KC_SPC)

#define FRG_NU FRK_NU 
#define FRG_SY FRK_SY
#define SY_NU  MO(_ORANGE_SYMBOL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_FROG_BASE] = LAYOUT_ortho_3x6_3(
        KC_F,    KC_A,    KC_R,    KC_W,    KC_P,    KC_BSPC,
        KC_O,    KC_E,    KC_H,    KC_T,    KC_D,    OSM(KC_LSFT),
        KC_U,    KC_I,    KC_N,    KC_S,    KC_Y,    KC_ENT,
        GRN_BS,  FRG_NU,  FRG_SY 
   ),

   [_GREEN_BASE] = LAYOUT_ortho_3x6_3(
        KC_TAB,  KC_QUOT, KC_B,    KC_M,    KC_J,    _______,
        KC_Q,    KC_Z,    KC_L,    KC_C,    KC_V,    CW_TOGG, 
        KC_COMM, KC_DOT,  KC_K,    KC_G,    KC_X,    KC_DOT,
        GRN_BS,  FRG_NU,  KC_COMM 
   ),

   [_FROG_NUMBER] = LAYOUT_ortho_3x6_3(
        KC_ASTR, KC_7,    KC_8,    KC_9,    KC_MINUS,_______,
        KC_PSLS, KC_4,    KC_5,    KC_6,    KC_PLUS, OSM(KC_LSFT), 
        KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
        GRN_NU,  FRG_NU,  FRG_SY 
   ),

   [_GREEN_NUMBER] = LAYOUT_ortho_3x6_3(
        KC_TAB,  KC_F7,   KC_F8,   KC_F9,   KC_QUOT, _______,
        KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_F12,  CW_TOGG, 
        KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_DLR,  KC_DOT,
        GRN_BS,  FRG_NU,  KC_COMM  
   ),

   [_SYMBOL] = LAYOUT_ortho_3x6_3(
        KC_QUES, KC_AMPR, KC_ASTR, KC_COLN, KC_SCLN, _______,
        KC_SLSH, KC_EXLM, KC_MINUS,KC_AT,   KC_UNDS, OSM(KC_LSFT), 
        KC_DQT,  KC_LT,   KC_LPRN, KC_LBRC, KC_LCBR, KC_ENT,
        GRN_SY,  SY_NU,   FRG_SY 
   ),


   [_GREEN_SYMBOL] = LAYOUT_ortho_3x6_3(
        KC_TAB,  KC_PLUS, KC_EQL,  KC_DLR,  KC_HASH, _______,
        KC_BSLS, KC_PERC, KC_PIPE, KC_TILD, KC_CIRC, CW_TOGG, 
        KC_GRV,  KC_GT,   KC_RPRN, KC_RBRC, KC_RCBR, KC_DOT,
        GRN_SY,  SY_NU,   KC_COMM 
   ),

   [_ORANGE_SYMBOL] = LAYOUT_ortho_3x6_3(
        QK_BOOT, KC_SCRL, KC_PSCR, XXXXXXX, XXXXXXX, _______,
        KC_LEFT, XXXXXXX, XXXXXXX, OSM(KC_LGUI), KC_RGHT, OSM(KC_LSFT), 
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MCTL, XXXXXXX, KC_DOT,
        KC_SPC,  SY_NU,   FRG_SY 
   ),

   [_ORANGE] = LAYOUT_ortho_3x6_3(
        KC_ESC,  KC_HOME, KC_END,  KC_BRK,  KC_PGUP, _______,
        KC_INS,  OSM(KC_LCTL),    OSM(KC_LALT),    KC_UP,    KC_PGDN, OSM(KC_LSFT), 
        KC_DEL,  KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOT,
        KC_SPC,  _______, FRG_SY 
   )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return arlaneenalra_layer_state(state);
}

bool oled_task_user(void) {
  oled_render_layer_state(0, 0);
  
  oled_render_mod_status(0, 11);
  
   return false;
}

#endif // OLED_ENABLE

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 
  uprintf("KL: kc: 0x%04X, 0x%04X col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, FRK_NU, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count); 

  if (record->event.pressed) {
    switch(keycode) {
      case FRK_NU:
        layer_move(_ORANGE);
        break;

      case FRK_SY:
        layer_move(_ORANGE_SYMBOL);
        break;
    }
  }
  return true;
}

