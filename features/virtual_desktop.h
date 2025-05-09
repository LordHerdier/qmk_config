#pragma once

#include QMK_KEYBOARD_H

/**
 * @file virtual_desktop.h
 * @brief Virtual Desktop Management for Windows
 * 
 * This module provides functions to manage Windows virtual desktops directly from QMK.
 * It allows for:
 *   - Switching between virtual desktops (1-N)
 *   - Moving the active window to a different virtual desktop
 *   - Tracking the current virtual desktop
 * 
 * Usage in keymap.c:
 *   1. Include this header: #include "features/virtual_desktop.h"
 *   2. Add `process_virtual_desktop(keycode, record)` to your process_record_user function
 *   3. Define virtual desktop keycodes (VD_1, VD_2, etc.) in your keymap
 * 
 * Hold SHIFT when pressing a VD key to move the active window to that desktop.
 */

/**
 * @brief Process virtual desktop keycodes
 * 
 * This function should be called from process_record_user() to handle
 * the virtual desktop keycodes (VD_1 through VD_9).
 * 
 * @param keycode The keycode to process
 * @param record The keyrecord containing event information
 * @return false if the keycode was processed, true otherwise
 * 
 * @example
 * bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *     // Process virtual desktop keycodes
 *     if (!process_virtual_desktop(keycode, record)) return false;
 *     
 *     // Other keycode processing...
 *     return true;
 * }
 */
bool process_virtual_desktop(uint16_t keycode, keyrecord_t *record);

/**
 * @brief Switch to the specified virtual desktop
 * 
 * Sends the appropriate key sequences to switch to the specified virtual desktop.
 * Uses Win+Ctrl+Left/Right to navigate between desktops.
 * 
 * @param vd The virtual desktop number to switch to (1-based index)
 * 
 * @note For best results, disable animation effects in Windows settings
 *       (accessibility -> Visual Effects -> Animation Effects)
 */
void move_vd(int8_t vd);

/**
 * @brief Move the current window to a different virtual desktop
 * 
 * Moves the currently active window to the specified virtual desktop,
 * then switches to that desktop.
 * 
 * @param vd The virtual desktop number to move the window to (1-based index)
 * 
 * @note This simulates the Windows UI interaction, so changes to the
 *       Windows UI may require updates to this implementation.
 */
void move_window_to_vd(int8_t vd);

/**
 * @brief Get the current virtual desktop number
 * 
 * @return The current virtual desktop number (1-based index)
 */
int8_t get_current_vd(void);

/**
 * @brief Set the maximum number of virtual desktops
 * 
 * Configures the maximum number of virtual desktops that the module will recognize.
 * This should match the number of virtual desktops configured in Windows.
 * 
 * @param max The maximum number of virtual desktops (default is 9)
 */
void set_vd_max(int8_t max); 