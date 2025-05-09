#include "virtual_desktop.h"
#include "custom_keycodes.h"
#include "print.h"
#include "wait.h"

/**
 * @file virtual_desktop.c
 * @brief Implementation of Windows virtual desktop management
 * 
 * This file implements the functions defined in virtual_desktop.h for
 * managing Windows virtual desktops. The implementation mimics user
 * interactions with the Windows UI to switch virtual desktops and
 * move windows between them.
 */

// ======================= STATE VARIABLES =======================

/**
 * @brief Current virtual desktop (1-based index)
 * 
 * Keeps track of which virtual desktop we're currently on.
 * Modified only by move_vd().
 */
static int8_t current_vd = 1;

/**
 * @brief Target virtual desktop for the current operation
 * 
 * Temporary storage for the desktop we're switching to.
 * Used in process_virtual_desktop() to pass the target to move functions.
 */
static int8_t target_vd = 0;

/**
 * @brief Maximum number of virtual desktops (default: 9)
 * 
 * Defines the highest virtual desktop number allowed.
 * Can be configured with set_vd_max().
 */
static int8_t vd_max = 9;

// ======================= PUBLIC FUNCTIONS =======================

/**
 * @brief Get the current virtual desktop number
 * 
 * Implementation of get_current_vd() defined in the header.
 * Simply returns the current virtual desktop tracking variable.
 */
int8_t get_current_vd(void) {
    return current_vd;
}

/**
 * @brief Set the maximum number of virtual desktops
 * 
 * Implementation of set_vd_max() defined in the header.
 * Updates the vd_max variable to match the Windows configuration.
 */
void set_vd_max(int8_t max) {
    if (max >= 1) {
        vd_max = max;
    }
}

/**
 * @brief Switch to the specified virtual desktop
 * 
 * Implementation of move_vd() defined in the header.
 * This function works by simulating Win+Ctrl+Arrow key combinations
 * to navigate between Windows virtual desktops.
 * 
 * @param vd Target virtual desktop (1-based index)
 */
void move_vd(int8_t vd) {
  // Validate the target desktop
  if (vd < 1 || vd > vd_max || vd == current_vd) return;

  dprintf("▶ Switching to VD %d\n", vd);

  // Calculate how many desktops to move left or right
  int8_t diff = vd - current_vd;

  // Switch based on direction
  if (diff < 0) {
    // Need to move left (lower desktop number)
    register_code(KC_LCTL);
    register_code(KC_LGUI);
    
    // Send the left arrow key the required number of times
    for (int8_t i = 0; i < -diff; i++) {
      tap_code(KC_LEFT);
      // Uncomment to add delay between keypresses if needed
      // wait_ms(50);
    }
    
    // Release modifiers
    unregister_code(KC_LGUI);
    unregister_code(KC_LCTL);
  } else if (diff > 0) {
    // Need to move right (higher desktop number)
    register_code(KC_LCTL);
    register_code(KC_LGUI);
    
    // Send the right arrow key the required number of times
    for (int8_t i = 0; i < diff; i++) {
      tap_code(KC_RGHT);
      // Uncomment to add delay between keypresses if needed
      // wait_ms(50);
    }
    
    // Release modifiers
    unregister_code(KC_LGUI);
    unregister_code(KC_LCTL);
  }

  // Update the tracking variable
  current_vd = vd;
}

/**
 * @brief Move the current window to a different virtual desktop
 * 
 * Implementation of move_window_to_vd() defined in the header.
 * This function simulates the Windows UI interaction sequence required
 * to move a window to another virtual desktop.
 * 
 * The sequence is:
 * 1. Open Task View (Win+Tab)
 * 2. Open window context menu (App key)
 * 3. Navigate to "Move to" submenu
 * 4. Select the target desktop
 * 5. Exit Task View
 * 6. Switch to the target desktop
 * 
 * @param vd Target virtual desktop (1-based index)
 */
void move_window_to_vd(int8_t vd) {
  // Validate the target desktop
  if (vd < 1 || vd > vd_max || vd == current_vd) return;

  dprintf("▶ Moving window to VD %d\n", vd);

  // Step 1: Open Task View (Win+Tab)
  // First ensure Shift is not pressed (can interfere with Win+Tab)
  unregister_code(KC_LSFT);
  // Send Win+Tab
  tap_code16(LGUI(KC_TAB));
  // Wait for Task View to open
  wait_ms(400);

  // Step 2: Open window context menu (App key)
  // Make sure modifiers are released
  unregister_code(KC_LSFT);
  unregister_code(KC_TAB);
  unregister_code(KC_LGUI);
  // Send App/Menu key
  tap_code(KC_APP);
  wait_ms(100);

  // Step 3: Navigate to "Move to" submenu
  // Move down to the "Move to" menu item
  tap_code(KC_DOWN);
  tap_code(KC_DOWN);
  wait_ms(125);
  // Open the submenu
  tap_code(KC_RGHT);
  wait_ms(125);

  // Step 4: Select the target desktop
  // The menu omits the current desktop, so indices need to be adjusted
  int8_t idx = (vd < current_vd) ? vd : vd - 1;
  // Move down to the target desktop in the menu
  for (int8_t i = 1; i < idx; i++) {
      tap_code(KC_DOWN);
      // Uncomment to add delay between keypresses if needed
      // wait_ms(20);
  }
  // Select the desktop
  tap_code(KC_ENT);
  // Uncomment to add delay if needed
  // wait_ms(50);

  // Step 5: Exit Task View
  tap_code(KC_ESC);
  wait_ms(200);

  // Step 6: Switch to the target desktop
  move_vd(vd);
}

/**
 * @brief Process virtual desktop keycodes
 * 
 * Implementation of process_virtual_desktop() defined in the header.
 * This function handles the virtual desktop keycodes (VD_1 through VD_9)
 * and calls the appropriate function based on modifiers.
 * 
 * If SHIFT is held when pressing a VD key, the window will be moved.
 * Otherwise, it will just switch to the desktop.
 * 
 * @param keycode The keycode to process
 * @param record The keyrecord containing event information
 * @return false if the keycode was processed, true otherwise
 */
bool process_virtual_desktop(uint16_t keycode, keyrecord_t *record) {
    // Only process on key press, and only process VD_* keycodes
    if (record->event.pressed && keycode >= VD_START && keycode < VD_END) {
        // Calculate the desktop number from the keycode
        target_vd = keycode - VD_START;
        dprintf("▶ VD %d key pressed\n", target_vd);

        // Skip if we're already on this desktop
        if (target_vd == current_vd) {
            dprint("▶ Already here – no action\n");
            return false;
        }

        // If SHIFT is held, move the window; otherwise just switch desktop
        if (get_mods() & MOD_MASK_SHIFT) {
            move_window_to_vd(target_vd);
        } else {
            move_vd(target_vd);
        }
        
        // Return false to indicate we've handled this keycode
        return false;
    }
    
    // Return true to let QMK continue processing this keycode
    return true;
} 