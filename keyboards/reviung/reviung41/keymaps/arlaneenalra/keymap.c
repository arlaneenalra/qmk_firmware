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
#include <stdio.h>

#include <arlaneenalra.h>

void log_rgblight(void);

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

char rgb_state[4][8] = {
  {},
  {},
  {},
  {}
};

bool oled_task_user(void) {
	oled_render_layer_state(10, 0);
	oled_render_mod_status(0, 0);

  oled_set_cursor(16, 0);
  oled_write(rgb_state[0], false);
  oled_set_cursor(16, 1);
  oled_write(rgb_state[1], false);
  oled_set_cursor(16, 2);
  oled_write(rgb_state[2], false);
  oled_set_cursor(16, 3);
  oled_write(rgb_state[3], false);

	return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  log_rgblight();

  return process_arlaneenalra_keycode(keycode, record);
}

void log_rgblight(void) {
  snprintf(rgb_state[0], 8, "e:%i", rgblight_is_enabled()); 
  snprintf(rgb_state[1], 8, "h:%x", rgblight_get_hue()); 
  snprintf(rgb_state[2], 8, "s:%x", rgblight_get_sat()); 
  snprintf(rgb_state[3], 8, "v:%x", rgblight_get_val());
}

void keyboard_post_init_user(void) {
  log_rgblight();

  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

