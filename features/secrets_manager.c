/**
 * @file secrets_manager.c
 * @brief Secure secrets management system for QMK keyboards
 *
 * This module provides a complete secrets management system that allows:
 * - Storing and retrieving secrets securely
 * - PIN-based authentication to unlock secrets
 * - Auto-locking after timeout for security
 * - Visual status indicators through RGB
 * - Secure typing of secrets directly from the keyboard
 */

#include QMK_KEYBOARD_H
#include "features/secrets_manager.h"
#include <string.h>
#include "print.h"

// ==== SECRETS DEFINITIONS ====

// Define the actual secret string constants
#define X(name, val) const char * const name = val;
SECRETS_LIST(X)
#undef X

// Build the lookup array from the same list
const char * const secret_list[] = {
#define X(name, val) name,
  SECRETS_LIST(X)
#undef X
};

// Calculate the secret count
const uint8_t SECRET_COUNT = sizeof(secret_list) / sizeof(secret_list[0]);

/**
 * @brief Retrieve a secret by its index
 *
 * @param i The index of the secret to retrieve
 * @return const char* Pointer to the secret string, or NULL if index is invalid
 */
const char *get_secret(uint8_t i) {
  return (i < SECRET_COUNT) ? secret_list[i] : NULL;
}

// ==== STATE VARIABLES ====

/**
 * @brief Tracks whether secrets are currently unlocked and accessible
 */
static bool secrets_unlocked = false;

/**
 * @brief Timeout in milliseconds after which secrets are automatically locked
 * Can be overridden in config.h
 */
#ifndef LOCK_TIMEOUT_MS
#define LOCK_TIMEOUT_MS 300000  // Default: 5 minutes
#endif

/**
 * @brief Timestamp of the last successful unlock, used for auto-lock timeout
 */
static uint32_t unlock_timer = 0;

/**
 * @brief Tracks whether the keyboard is currently in PIN entry mode
 */
static bool pin_entry_mode = false;

/**
 * @brief Maximum length for the PIN input buffer
 */
#define MAX_PIN_LENGTH 32

/**
 * @brief Buffer to store PIN digits as they're entered
 */
static char pin_buffer[MAX_PIN_LENGTH];

/**
 * @brief Current position in the PIN buffer
 */
static uint8_t pin_index = 0;

// ==== PUBLIC STATE QUERY FUNCTIONS ====

/**
 * @brief Check if secrets are currently unlocked
 *
 * @return true Secrets are unlocked and accessible
 * @return false Secrets are locked
 */
bool is_secrets_unlocked(void) {
    return secrets_unlocked;
}

/**
 * @brief Check if PIN entry mode is active
 *
 * @return true PIN entry mode is active
 * @return false PIN entry mode is not active
 */
bool is_pin_entry_mode(void) {
    return pin_entry_mode;
}

// ==== COMMAND FUNCTIONS ====

/**
 * @brief Lock the secrets system
 * 
 * This clears the unlocked state and PIN buffer, and exits PIN entry mode.
 */
void secrets_lock(void) {
    dprint("▶ LOCK command received – locking secrets\n");
    secrets_unlocked = false;
    pin_entry_mode = false;
    pin_index = 0;
    pin_buffer[0] = '\0';
}

/**
 * @brief Enter PIN entry mode to unlock secrets
 * 
 * If secrets are already unlocked, this will lock them instead.
 */
void enter_pin_mode(void) {
    if (!secrets_unlocked) {
        dprint("▶ Entering PIN mode\n");
        pin_entry_mode = true;
        pin_index = 0;
    } else {
        secrets_lock();
    }
}

// ==== PIN PROCESSING ====

/**
 * @brief Process keystrokes during PIN entry mode
 *
 * Handles digit input, Enter to submit, and Escape to cancel.
 * Valid PIN unlocks the secrets system.
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by PIN processing
 */
bool process_pin_entry(uint16_t keycode, keyrecord_t *record) {
    // Only process key presses during PIN entry mode
    if (!pin_entry_mode || !record->event.pressed) {
        return true;
    }

    dprintf("▶ PIN mode: keycode=%d\n", keycode);

    // Handle digit keys (main row and numpad)
    if ((keycode >= KC_1 && keycode <= KC_0) || 
        (keycode >= KC_KP_1 && keycode <= KC_KP_0))
    {
        uint8_t val;
        // Convert keycode to numeric value
        if (keycode >= KC_KP_1 && keycode <= KC_KP_9) {
            val = (keycode - KC_KP_1) + 1;  // KP1→1, KP2→2, …
        } else if (keycode == KC_KP_0) {
            val = 0;
        } else {
            val = (keycode - KC_1) + 1;     // '1'→1, '2'→2, …
        }
        
        // Add digit to buffer if there's room
        if (pin_index < MAX_PIN_LENGTH - 1) {
            pin_buffer[pin_index++] = '0' + val;
            dprintf("▶ Digit added: %c (index=%d)\n", '0'+val, pin_index-1);
        } else {
            dprint("▶ PIN buffer full!\n");
        }
        return false;  // Consume the key
    }
    
    // Handle Enter key to submit PIN
    if (keycode == KC_PENT || keycode == KC_ENT) {
        // Null-terminate the PIN string
        pin_buffer[pin_index] = '\0';
        dprintf("▶ PIN entered: %s (length=%d)\n", pin_buffer, pin_index);
        
        // Validate against stored PIN
        if (!strcmp(pin_buffer, SECRET_PIN)) {
            dprint("▶ PIN CORRECT - Secrets unlocked!\n");
            secrets_unlocked = true;
            // Reset unlock timer
            unlock_timer = timer_read32();
        } else {
            dprint("▶ PIN INCORRECT - Access denied\n");
        }
        
        // Clean up and exit PIN mode
        dprint("▶ Exiting PIN mode\n");
        pin_entry_mode = false;
        pin_index = 0;
        return false;  // Consume the key
    }
    
    // Handle Escape key to cancel PIN entry
    if (keycode == KC_ESC) {
        dprint("▶ PIN entry canceled\n");
        pin_entry_mode = false;
        pin_index = 0;
        return false;  // Consume the key
    }

    // Allow other keys to pass through
    return true;
}

/**
 * @brief Process keystrokes for secret-related keycodes
 *
 * Handles sending of secrets when their corresponding keys are pressed.
 * Blocks access to secrets when the system is locked.
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by secrets processing
 */
bool process_secret_keycodes(uint16_t keycode, keyrecord_t *record) {
    // Block secret macros if system is locked
    if (keycode >= E_PIN && keycode <= E_PASS4 && !secrets_unlocked) {
        return false;  // Silently consume the key
    }

    // Handle secret macro keycodes
    if (record->event.pressed && keycode >= E_SECRET_START && keycode < E_SECRET_END) {
        uint8_t idx = keycode - E_SECRET_START;
        const char *secret = get_secret(idx);
        if (secret) {
            // Type out the secret and press Enter
            send_string_with_delay(secret, 1);
            tap_code(KC_ENT);
        }
        // Consume the key
        return false;
    }

    // Allow other keys to pass through
    return true;
}

// ==== TIMER AND AUTO-LOCK ====

/**
 * @brief Process keystrokes for PIN_ENTRY keycode activation
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by PIN entry processing
 */
bool process_pin_entry_keycode(uint16_t keycode, keyrecord_t *record) {
    if (keycode == PIN_ENTRY && record->event.pressed) {
        enter_pin_mode();
        return false;
    }
    return true;
}

/**
 * @brief Timer task to handle auto-locking of secrets
 * 
 * This should be called regularly from matrix_scan_user()
 */
void secrets_timer_task(void) {
    // Check if timeout has elapsed since last unlock
    if (secrets_unlocked && timer_elapsed(unlock_timer) > LOCK_TIMEOUT_MS) {
        dprint("▶ Auto-lock timeout reached – locking secrets\n");
        secrets_unlocked = false;
        pin_entry_mode = false;
        pin_index = 0;
        pin_buffer[0] = '\0';
    }
}

/**
 * @brief Special handler for GUI+L key combination
 * 
 * Locks secrets when Windows lock shortcut is used
 */
void secrets_gui_lock(void) {
    dprint("▶ GUI+L detected – locking secrets\n");
    secrets_unlocked = false;
}

// ==== RGB INDICATORS ====

/**
 * @brief Get the current security state for RGB indicators
 *
 * @return uint8_t 0: Locked, 1: PIN entry mode, 2: Unlocked
 */
uint8_t secrets_get_indicator_state(void) {
    if (pin_entry_mode) {
        return 1; // PIN entry mode
    } else if (secrets_unlocked) {
        return 2; // Unlocked
    } else {
        return 0; // Locked
    }
} 