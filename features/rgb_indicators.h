/**
 * @file rgb_indicators.h
 * @brief RGB LED indicator functionality for keyboard status visualization
 * 
 * This module provides functionality to control RGB LEDs for indicating different
 * keyboard states such as active layer, caps lock, and PIN entry status.
 * Only enabled when RGB_MATRIX_ENABLE is defined.
 */

#pragma once

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
/**
 * @brief Implementation of RGB indicators functionality
 * 
 * This function handles the configuration of RGB LEDs to visually indicate:
 * - Current active layer (using specific keys in the number row)
 * - Caps Lock state (using the Caps Lock key LED)
 * - PIN entry status from the secrets manager (using key at index 97)
 * 
 * @return bool Returns false to allow the RGB matrix effects to continue processing
 */
bool rgb_indicators_implementation(void);
#endif 