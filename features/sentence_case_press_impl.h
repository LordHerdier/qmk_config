/**
 * @file sentence_case_press_impl.h
 * @brief Implementation of the sentence case feature's key press handler
 * 
 * This file provides the implementation for the sentence_case_press_user function,
 * which is called by the sentence case feature for each key press. The function
 * determines how each keypress should be categorized for sentence case tracking.
 * 
 * This file is meant to be directly included in keymap.c.
 */

/**
 * @brief Processes keypresses for sentence case handling
 * 
 * This function categorizes keypresses to help the sentence case feature
 * determine when to apply capitalization:
 * - Returns 'a' for letter keys (signals a letter was typed)
 * - Returns '.' for sentence-ending punctuation
 * - Returns '#' for other symbols/punctuation
 * - Returns ' ' for space
 * - Returns '\'' for quote
 * - Returns '\0' for modifier keys and other special keys (clears state)
 * 
 * @param keycode The keycode of the key being pressed
 * @param record Pointer to the keyrecord containing press information
 * @param mods Current state of modifier keys
 * @return Character representing how the key should be handled in sentence case
 */
char sentence_case_press_user(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    // First unwrap any home-row-mod keycodes into their plain letter equivalents
    // This allows home-row mods to work correctly with sentence case
    switch (keycode) {
        case CKC_A: keycode = KC_A; break;
        case CKC_R: keycode = KC_R; break;
        case CKC_S: keycode = KC_S; break;
        case CKC_T: keycode = KC_T; break;
        case CKC_D: keycode = KC_D; break;
        case CKC_H: keycode = KC_H; break;
        case CKC_N: keycode = KC_N; break;
        case CKC_E: keycode = KC_E; break;
        case CKC_I: keycode = KC_I; break;
        case CKC_O: keycode = KC_O; break;
        default:
            break;
    }

    // Only process keys when no modifiers are pressed (except for Shift or Right Alt/AltGr)
    // This prevents sentence case from triggering during keyboard shortcuts
    if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
        const bool shifted = mods & MOD_MASK_SHIFT; // Check if shift is held
        switch (keycode) {
            case KC_A ... KC_Z:
                return 'a';  // Any letter - returned as 'a' to indicate "letter" category
            
            case KC_DOT:  // Period key (. or >)
                // Return '.' only for the actual period, not the shift variant
                return !shifted ? '.' : '#';
            
            case KC_1:    // 1 or ! key
            case KC_SLSH: // / or ? key
                // Return '.' for shifted variants (! or ?) as they can end sentences
                return shifted ? '.' : '#';
            
            case KC_EXLM: // Direct ! key
            case KC_QUES: // Direct ? key
                return '.';  // These explicitly end sentences
            
            // Various symbol and punctuation keys that don't end sentences
            case KC_2 ... KC_0:       // digits & their shifted symbols
            case KC_AT ... KC_RPRN:   // @ # $ % ^ & * ( )
            case KC_MINS ... KC_SCLN: // - = [ ] \ ;
            case KC_UNDS ... KC_COLN: // _ + { } | :
            case KC_GRV:              // ` or ~
            case KC_COMM:             // , or <
                return '#';  // General symbols/punctuation marker
            
            case KC_SPC:
                return ' ';  // Space character
            
            case KC_QUOT:
                return '\''; // Quote character (tracked separately for special handling)
        }
    }

    // Any other key (modifiers, navigation, etc.) clears the sentence case state
    // This prevents unexpected capitalization when using keyboard shortcuts or navigation
    sentence_case_clear();
    return '\0';
} 