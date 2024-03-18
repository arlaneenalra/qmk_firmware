#include "arlaneenalra.h"

#include <modules/animations/animations.h>
#include <modules/oled_large/layers.h>

#ifndef OLED_NO_LAYER_MAP 
const uint8_t PROGMEM layer_render_map[] = {
 [_BASE] = SYM_BASE,
 [_LOWER] = SYM_LOWER,
 [_RAISE] = SYM_RAISE,
 [_ADJUST] = SYM_ADJUST,
 [_NAV] = SYM_NAV,
 [_NUMBER] = SYM_NUMBER,
   
 [_FROG_LETTER] = SYM_FROG,
 [_FROG_LETTER2] = SYM_LOWER
};

#endif

bool shutdown_user(bool jump_to_bootloader) {
  if (jump_to_bootloader) {
  	oled_render_boot();
  } 
  return false;
}

layer_state_t arlaneenalra_layer_state(layer_state_t state) {

  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_arlaneenalra_keycode(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case QK_BOOT:
        // Display a special logo prior to rebooting...
				oled_set_reboot(); 
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

      case QMK_NEWT:
        SEND_STRING(SS_LGUI("t"));
        break;

      case QMK_ALL:
        SEND_STRING(SS_LGUI("a"));
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

// Handle capsword and drop the -_ trick.
bool caps_word_press_user(uint16_t keycode) {
   switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}
