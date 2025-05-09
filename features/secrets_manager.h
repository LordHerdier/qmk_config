/**
 * @file secrets_manager.h
 * @brief Secure secrets management system for QMK keyboards
 *
 * This module provides a complete secrets management system that allows:
 * - Storing and retrieving secrets securely
 * - PIN-based authentication to unlock secrets
 * - Auto-locking after timeout for security
 * - Visual status indicators through RGB
 * - Secure typing of secrets directly from the keyboard
 *
 * To use this module:
 * 1. Define SECRETS_ENABLED in config.h
 * 2. Create a secrets.h file with your sensitive data
 * 3. Call secrets_timer_task() from matrix_scan_user()
 * 4. Process keystrokes with process_pin_entry() and process_secret_keycodes()
 */

#ifndef SECRETS_MANAGER_H
#define SECRETS_MANAGER_H

#if !defined(SECRETS_ENABLED) || (SECRETS_ENABLED != yes)
    #error "SECRETS_ENABLED must be defined as 'yes' in your config.h"
#endif

#include "secrets.h"
#include "custom_keycodes.h"

// ==== SECRET DECLARATIONS ====

/**
 * @brief Declare the secret constants as extern
 * These are defined in secrets_manager.c
 */
#define X(name, val) extern const char * const name;
SECRETS_LIST(X)
#undef X

/**
 * @brief Array of pointers to all secrets for easy access by index
 * This corresponds to keycodes E_PIN, E_PHRASE, E_PASS1, etc.
 */
extern const char * const secret_list[];

/**
 * @brief Number of secrets in the array
 */
extern const uint8_t SECRET_COUNT;

/**
 * @brief Get a secret by its index
 *
 * @param i Index of the secret to retrieve
 * @return const char* The secret string, or NULL if index is invalid
 */
const char *get_secret(uint8_t i);

// ==== STATE QUERY FUNCTIONS ====

/**
 * @brief Check if secrets are currently unlocked
 *
 * @return true Secrets are unlocked and accessible
 * @return false Secrets are locked
 */
bool is_secrets_unlocked(void);

/**
 * @brief Check if PIN entry mode is active
 *
 * @return true PIN entry mode is active
 * @return false PIN entry mode is not active
 */
bool is_pin_entry_mode(void);

// ==== COMMAND FUNCTIONS ====

/**
 * @brief Lock the secrets system
 * 
 * This clears the unlocked state and PIN buffer, and exits PIN entry mode.
 */
void secrets_lock(void);

/**
 * @brief Enter PIN entry mode to unlock secrets
 * 
 * If secrets are already unlocked, this will lock them instead.
 */
void enter_pin_mode(void);

/**
 * @brief Special handler for GUI+L key combination
 * 
 * Call this when Windows lock shortcut is pressed to also lock secrets
 */
void secrets_gui_lock(void);

// ==== KEYCODE PROCESSING ====

/**
 * @brief Process keystrokes for PIN_ENTRY keycode activation
 *
 * This function handles activation of PIN entry mode via dedicated keycode
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by PIN entry keycode processing
 */
bool process_pin_entry_keycode(uint16_t keycode, keyrecord_t *record);

/**
 * @brief Process keystrokes during PIN entry mode
 *
 * This function handles all PIN entry functionality:
 * - Digit entry (both number row and numpad)
 * - PIN submission (Enter)
 * - Cancellation (Escape)
 * - Authentication against stored PIN
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by PIN processing
 */
bool process_pin_entry(uint16_t keycode, keyrecord_t *record);

/**
 * @brief Process keystrokes for secret-related keycodes
 *
 * This function:
 * - Blocks access to secret keycodes when the system is locked
 * - Handles sending secrets when their corresponding keys are pressed
 *
 * @param keycode The QMK keycode being processed
 * @param record Key event record containing press/release info
 * @return true Allow QMK to process this key normally
 * @return false Key was consumed by secrets processing
 */
bool process_secret_keycodes(uint16_t keycode, keyrecord_t *record);

// ==== TIMER AND AUTO-LOCK ====

/**
 * @brief Timer task to handle auto-locking of secrets
 * 
 * Call this regularly from matrix_scan_user() to enable auto-locking
 * after the timeout period (LOCK_TIMEOUT_MS).
 */
void secrets_timer_task(void);

// ==== RGB INDICATORS ====

/**
 * @brief Get the current security state for RGB indicators
 *
 * This function returns a numeric value representing the security state
 * that can be used for RGB indicators.
 *
 * @return uint8_t 0: Locked, 1: PIN entry mode, 2: Unlocked
 */
uint8_t secrets_get_indicator_state(void);

#endif // SECRETS_MANAGER_H
