/**
 * @file features/process_meta_layer.h
 * @brief Meta layer handling functionality
 * 
 * This module handles the activation and deactivation of the meta layer,
 * which allows for GUI/Meta key combinations while maintaining a clean
 * separation of layers. It also implements special meta layer shortcuts
 * like Meta+L for locking secrets.
 */

#include QMK_KEYBOARD_H
#include "features/secrets_manager.h"

/**
 * @brief Initialize the meta layer functionality
 * 
 * Currently empty, but available if initialization is needed in the future.
 */
void meta_layer_init(void) { /* if you need it */ }

/**
 * @brief Process meta layer keycode events
 * 
 * This function handles two main responsibilities:
 * 1. Special Meta key combinations (e.g., Meta+L to lock secrets)
 * 2. Activating and deactivating the Meta layer with the META_LAYER keycode
 *
 * When the Meta layer is activated, the left GUI modifier is automatically
 * registered, allowing all subsequent keypresses to act as GUI/Meta combinations.
 * 
 * @param keycode The keycode being processed
 * @param record The keyrecord containing event information (pressed/released)
 * @return false if the keycode was handled by this function, true to continue processing
 */
bool process_meta_layer(uint16_t keycode, keyrecord_t *record) {
  // Special case: Meta+L combination to lock secrets
  // This still allows the Meta+L combination to be sent to the host OS
  if (keycode == KC_L && record->event.pressed) {
      uint8_t mods = get_mods();
      if (mods & MOD_MASK_GUI) {
          // Lock secrets when Meta+L is pressed
          secrets_gui_lock();
      }
  }

  // Exit early if not the META_LAYER keycode
  if (keycode != META_LAYER) return true;
  
  if (record->event.pressed) {
    // On keypress: activate meta layer and register left GUI modifier
    layer_on(_META); register_mods(MOD_BIT(KC_LGUI));
    dprint("▶ Meta layer on\n");
  } else {
    // On key release: deregister left GUI modifier and deactivate meta layer
    unregister_mods(MOD_BIT(KC_LGUI)); layer_off(_META);
    dprint("▶ Meta layer off\n");
  }

  // Return false to indicate we've handled this keycode
  return false;
}