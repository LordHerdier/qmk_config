/**
 * @file custom_keycodes.h
 * @brief Custom keycodes definitions for keyboard firmware
 * 
 * This file defines all custom keycodes used in the firmware beyond what QMK provides.
 * These include shortcuts, macros, and special functions implemented through custom handlers.
 */

#pragma once

/**
 * @enum custom_keycodes
 * @brief Enumeration of all custom keycodes for the keyboard
 * 
 * These keycodes extend the basic QMK functionality with custom behaviors
 * handled in process_record_user() and other processing functions.
 */
enum custom_keycodes {
    // Secret keycodes range
    E_SECRET_START = SAFE_RANGE, /**< Marker for the start of secret keycodes */
    E_PIN = E_SECRET_START,      /**< Keycode to enter a PIN code */
    E_PHRASE,                    /**< Keycode to enter a saved phrase */
    E_PASS1,                     /**< Keycode for password #1 */
    E_PASS2,                     /**< Keycode for password #2 */
    E_PASS3,                     /**< Keycode for password #3 */
    E_PASS4,                     /**< Keycode for password #4 */
    E_SECRET_END,                /**< Marker for the end of secret keycodes */

    // Other custom keycodes
    PIN_ENTRY,                   /**< Activates PIN entry mode */
    SENTENCE_CASE_TOGGLE,        /**< Toggles sentence case feature on/off */
    
    // Virtual desktop keycodes
    VD_START,                    /**< Marker for start of virtual desktop keycodes */
    VD_1 = VD_START + 1,         /**< Switch to virtual desktop 1 */
    VD_2,                        /**< Switch to virtual desktop 2 */
    VD_3,                        /**< Switch to virtual desktop 3 */
    VD_4,                        /**< Switch to virtual desktop 4 */
    VD_5,                        /**< Switch to virtual desktop 5 */
    VD_6,                        /**< Switch to virtual desktop 6 */
    VD_7,                        /**< Switch to virtual desktop 7 */
    VD_8,                        /**< Switch to virtual desktop 8 */
    VD_9,                        /**< Switch to virtual desktop 9 */
    VD_END,                      /**< Marker for end of virtual desktop keycodes */
    
    // Meta layer activation
    META_LAYER,                  /**< Activates the meta layer for additional functionality */
    
    // SMTD keycodes
    SMTD_KEYCODES_BEGIN,         /**< Marker for start of SMTD keycodes */
    CKC_A,                       /**< Home row mod for 'A' key */
    CKC_R,                       /**< Home row mod for 'R' key */
    CKC_S,                       /**< Home row mod for 'S' key */
    CKC_T,                       /**< Home row mod for 'T' key */
    CKC_D,                       /**< Home row mod for 'D' key */
    CKC_H,                       /**< Home row mod for 'H' key */
    CKC_N,                       /**< Home row mod for 'N' key */
    CKC_E,                       /**< Home row mod for 'E' key */
    CKC_I,                       /**< Home row mod for 'I' key */
    CKC_O,                       /**< Home row mod for 'O' key */
    SMTD_KEYCODES_END,           /**< Marker for end of SMTD keycodes */
    
    // Cycling keycodes
    CYC_S,                       /**< Cycle through variations of 'S' key (possibly for sending ß, etc.) */
    
    // Run command keycodes
    RUN_CMD_START,               /**< Marker for start of application launcher keycodes */
    RUN_WT,                      /**< Launch Windows Terminal */
    RUN_FILES,                   /**< Launch File Explorer */
    RUN_BROWSER,                 /**< Launch web browser */
    RUN_NOTEPAD,                 /**< Launch Notepad */
    RUN_CMD_END,                 /**< Marker for end of application launcher keycodes */
    
    // Custom safe range for other modules
    NEW_SAFE_RANGE               /**< Starting point for other modules to define their keycodes */
};