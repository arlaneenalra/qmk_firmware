#include "layers.h"

static bool reboot = false;

void oled_set_reboot(void) {
	reboot = true;
}

void oled_render_boot(void) {
	if (!reboot) {
		return;
	}

  oled_clear();
  for (int i = 0; i < 16; i++) {
    oled_set_cursor(0, i);
    oled_write_P(PSTR("BOOT "), false);
  }

  oled_render_dirty(true);
} 

