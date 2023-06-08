/* Copyright 2020 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <arlaneenalra.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = BASE_LAYER(LAYOUT, FIVE_KEY_SPACE),
  
  [_LOWER] = LOWER_LAYER(LAYOUT, FIVE_KEY_SPACE),
  
  [_RAISE] = RAISE_LAYER(LAYOUT, FIVE_KEY_SPACE),

  [_ADJUST] = ADJUST_LAYER(LAYOUT, FIVE_KEY_SPACE),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
	oled_render_layer_state(10, 0);
	oled_render_mod_status(0, 0);

	return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_arlaneenalra_keycode(keycode, record);
}

/*
 void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
} */

