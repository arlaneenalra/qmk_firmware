#pragma once

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute

#include <modules/animations/animations.h>
#include <modules/oled_large/layers.h>

#endif

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


bool process_arlaneenalra_keycode(uint16_t keycode, keyrecord_t *record);


enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

/*
#define LOWER  TT(_LOWER)
#define RAISE  TT(_RAISE)
#define ADJUST TT(_ADJUST)
*/

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

#define SIX_KEY_SPACE KC_SPC,  KC_SPC
#define FIVE_KEY_SPACE KC_SPC

#define SIX_TRANSPARENT _______,  _______
#define FIVE_TRANSPARENT _______

#define BASE_LAYER(_LAYOUT_, _SPACE_) _LAYOUT_( \
      QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC, \
      CW_TOGG,  HOME_A,  HOME_S,  HOME_D,  HOME_F,    KC_G,                         KC_H,  HOME_J,  HOME_K,  HOME_L,HME_SCLN, KC_QUOT, \
       KC_TAB,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT, \
                                           KC_INS,   LOWER,         _SPACE_,       RAISE,  KC_DEL )

#define LOWER_LAYER(_LAYOUT_, _SPACE_) _LAYOUT_( \
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, \
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_MCTL,                      KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, \
      _______,QMK_UNDO, QMK_CUT, QMK_CPY,QMK_PSTE, KC_LPAD,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, _______, \
                                          _______, _______,         _SPACE_,     _______, _______ )

#define RAISE_LAYER(_LAYOUT_, _SPACE_) _LAYOUT_( \
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, _______, _______, _______, _______, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX,QMK_LNCH,QMK_PMKN,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,  KC_GRV, _______, \
                                          _______, _______,         _SPACE_,     _______, _______ )

#define ADJUST_LAYER(_LAYOUT_, _SPACE_) _LAYOUT_( \
      QK_BOOT, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, RGB_TOG,                     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_VOLD, KC_VOLU, \
      QK_RBT, _______, _______, _______, _______, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,  KC_F12, \
      QK_MAKE,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, \
                                          _______, _______,         _SPACE_,     _______, _______ )

