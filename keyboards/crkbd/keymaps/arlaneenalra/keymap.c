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

#include <arlaneenalra.h>

KEYMAP_FROG(LAYOUT_split_3x6_3, MATRIX_ROWS, MATRIX_COLS)

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  } 
  
  return OLED_ROTATION_270;
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

layer_state_t layer_state_set_user(layer_state_t state) {
  return arlaneenalra_layer_state(state);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
      oled_render_layer_state(0, 0);
      oled_render_frog_state(0, 5, get_highest_layer(default_layer_state) == _FROG_LETTER);
      oled_render_mod_status(0, 11);
  } else {
    #ifndef OLED_ANIMATIONS
    oled_render_logo();
    #else
    oled_render_anim();
    #endif
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_arlaneenalra_keycode(keycode, record);
}

#endif // OLED_ENABLE
