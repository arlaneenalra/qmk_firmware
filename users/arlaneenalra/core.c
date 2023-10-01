#include "arlaneenalra.h"

#include <modules/animations/animations.h>
#include <modules/oled_large/layers.h>


void shutdown_user(void) {
	oled_render_boot();
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
