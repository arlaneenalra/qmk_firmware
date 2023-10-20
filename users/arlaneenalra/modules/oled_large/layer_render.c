#include "layers.h"

extern const uint8_t PROGMEM layer_render_map[];

static const char PROGMEM layer_symbols[][6] = {
 { 0x00, 0x00, 0x00, 0x00, 0x00 }, // Blank
                                   
 { 0x33, 0xCC, 0x33, 0xCC, 0x33 }, // Base
 { 0x10, 0x20, 0x7F, 0x20, 0x10 }, // Lower
 { 0x04, 0x02, 0x7F, 0x02, 0x04 }, // Raise
 { 0x14, 0x22, 0x7F, 0x22, 0x14 }, // Adjust 
 
 { 0x40, 0xEA, 0x1B, 0xEA, 0x40 }, // Nav
 { 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // Number
 { 0xEA, 0x35, 0xE6, 0x35, 0xEA }, // Frog
                                   
};


static const char PROGMEM mod_symbols[][6] = {
 { 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C }, // shift 
 { 0x04, 0x02, 0x01, 0x01, 0x02, 0x04 }, // ctl
 { 0x03, 0x07, 0x0C, 0x18, 0x71, 0x61 }, // alt
 { 0x33, 0x2D, 0x12, 0x12, 0x2D, 0x33 }, // cmd
 { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }  // caps word
};


static char pixel_buffer[32];

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

void oled_render_mod_status(uint8_t col, uint8_t row) {
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

  oled_set_cursor(col, row); 
  oled_write_mod_row(
      shift_symbol, mod_status & MOD_MASK_SHIFT, 0, 0);
  oled_write_mod_row(
      SYM_CTRL, mod_status & MOD_MASK_CTRL, 1, 0);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(col, row + 1);
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      shift_symbol, mod_status & MOD_MASK_SHIFT, 0, 1);
  oled_write_mod_row(
      SYM_CTRL, mod_status & MOD_MASK_CTRL, 1, 1);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(col, row + OLED_MOD_STEP_2);
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      SYM_ALT, mod_status & MOD_MASK_ALT, 0, 0);
  oled_write_mod_row(
      SYM_CMD, mod_status & MOD_MASK_GUI, 1, 0);
  
  oled_write_raw(pixel_buffer, 32);

  oled_set_cursor(col, row + OLED_MOD_STEP_3); 
  oled_write_raw(blank, 1);
  oled_write_mod_row(
      SYM_ALT, mod_status & MOD_MASK_ALT, 0, 1);
  oled_write_mod_row(
      SYM_CMD, mod_status & MOD_MASK_GUI, 1, 1);
  
  oled_write_raw(pixel_buffer, 32);
}

void oled_render_big_sym(uint8_t col, uint8_t row, uint8_t sym) {

  oled_set_cursor(col, row);
  oled_write_layer_row(sym, 0);
  oled_set_cursor(col, row + 1);
  oled_write_layer_row(sym, 1);
  oled_set_cursor(col, row + 2);
  oled_write_layer_row(sym, 2);
  oled_set_cursor(col, row + 3);
  oled_write_layer_row(sym, 3);
}

void oled_render_layer_state(uint8_t col, uint8_t row) {
  uint8_t sym = get_highest_layer(layer_state);

  oled_render_big_sym(col, row, pgm_read_byte(&layer_render_map[sym]));
}

void oled_render_frog_state(uint8_t col, uint8_t row, bool is_frog) {
  uint8_t sym;

  // Short term hack to account for frog mode
  if (is_frog) {
    sym = SYM_FROG;
  } else {
    sym = SYM_BLANK;
  }
 
  oled_render_big_sym(col, row, sym);
}
