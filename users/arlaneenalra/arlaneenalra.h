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
