#include QMK_KEYBOARD_H
#include "config.h"
#include "keymaps.h"
#include "custom_keycodes.h"

#include "quantum.h"
#include "action_layer.h"
#include "print.h"
#include <string.h>

#include "features/sentence_case.h"
#include "features/run_cmds.h"
#include "features/secrets_manager.h"
#include "features/virtual_desktop.h"
#include "features/rgb_indicators.h"
#include "features/process_meta_layer.h"

/* The following files are meant to be included directly in keymap.c 
*  We do this to trick the compiler into treating them as if they were defined in this file, as the
*  parent modules will complain if they're defined elsewhere.
*/
#include "features/sentence_case_press_impl.h" // Include the sentence case press implementation

void matrix_scan_user(void) {
    secrets_timer_task();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Process the keycodes in the order of priority
  return process_record_sentence_case(keycode, record) &&
         process_run_cmd(keycode, record) &&
         process_meta_layer(keycode, record) &&
         process_virtual_desktop(keycode, record) &&
         process_pin_entry(keycode, record) &&
         process_pin_entry_keycode(keycode, record) &&
         process_secret_keycodes(keycode, record);

    return true; // otherwise, let QMK send the key normally
}

#ifdef RGB_MATRIX_ENABLE
// Main RGB function that QMK will look for - calls our implementation
bool rgb_matrix_indicators_user(void) {
    return rgb_indicators_implementation();
}
#endif

void keyboard_post_init_user(void) {
    debug_enable   = false;   // master debug switch
    debug_matrix   = false;  // raw switch-matrix events
    debug_keyboard = false;   // uncomment if you want keycode-by-keycode logs
}




