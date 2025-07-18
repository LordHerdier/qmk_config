/**
 * @file rgb_indicators.c
 * @brief Implementation of RGB indicator functionality for visual keyboard status
 * 
 * This module configures RGB LEDs to provide visual feedback about:
 * - PIN/secret entry status using the secrets manager
 * - Current active layer
 * - Caps Lock state
 * 
 * The RGB indicators provide a quick visual reference for the current keyboard state,
 * making it easier to identify which layer is active and key system states.
 */

#include "quantum.h"
#include "layers.h"
#include "features/secrets_manager.h"
#include "config.h"

#ifdef RGB_MATRIX_ENABLE
/**
 * @brief Main implementation for RGB indicator functionality
 * 
 * This function is called by rgb_matrix_indicators_user() in keymap.c to
 * configure RGB LEDs based on current keyboard state.
 * 
 * @return bool Returns false to allow RGB matrix effects to continue processing
 */
bool rgb_indicators_implementation(void) {
  // ------------- PIN status indicator on KC_P0 (idx 97) -------------
  // This visualizes the current state of PIN/secret entry from the secrets manager
  {
      const uint8_t pin_idx = 97; // Key index for the PIN indicator (Numpad 0)
      HSV hsv_pin;
      
      // Get the indicator state from the secrets manager
      uint8_t state = secrets_get_indicator_state();
      
      if (state == 1) {
          // Yellow: PIN entry mode active (waiting for PIN input)
          hsv_pin = (HSV){ .h = 43,  .s = 255, .v = 255 };
      } else if (state == 2) {
          // Green: PIN successfully entered, authentication successful
          hsv_pin = (HSV){ .h = 85,  .s = 255, .v = 255 };
      } else {
          // Red: Default state or PIN entry failed/locked out
          hsv_pin = (HSV){ .h = 0,   .s = 255, .v = 255 };
      }
      
      // Convert HSV to RGB and set the LED color
      RGB rgb_pin = hsv_to_rgb(hsv_pin);
      rgb_matrix_set_color(pin_idx, rgb_pin.r, rgb_pin.g, rgb_pin.b);
  }

  // ------------- Autocorrect status indicator on TAB (idx 36) -------------
//   {
//       const uint8_t autocorrect_idx = 36; // Key index for the TAB key
//       HSV hsv_autocorrect;
      
//       if (autocorrect_is_enabled()) {
//           // Purple: Autocorrect is enabled
//           hsv_autocorrect = (HSV){ .h = 220, .s = 255, .v = 255 };
//       } else {
//           // Off when autocorrect is disabled
//           hsv_autocorrect = (HSV){ .h = 0, .s = 0, .v = 0 };
//       }
      
//       // Convert HSV to RGB and set the LED color
//       RGB rgb_autocorrect = hsv_to_rgb(hsv_autocorrect);
//       rgb_matrix_set_color(autocorrect_idx, rgb_autocorrect.r, rgb_autocorrect.g, rgb_autocorrect.b);
//   }

  // ------------- Layer state indicators -------------
  // Get the current active layer
  layer_state_t st = layer_state;
  uint8_t layer = biton32(st); // Find the highest active layer

  // 1) Clear grave key and number row (keys 18-28) and Caps key (54)
  // This ensures we start with a clean slate for our indicators
  for (uint8_t i = 18; i <= 28; i++) {
      rgb_matrix_set_color(i, 0, 0, 0);
  }
  rgb_matrix_set_color(54, 0, 0, 0);

  // 2) Caps Lock indicator handling
  // Check host LED state and indicate Caps Lock status with the Caps key LED
  if (host_keyboard_led_state().caps_lock) {
      // Pure white at full brightness when Caps Lock is on
      HSV hsv_caps = { .h = 0, .s = 0, .v = 255 };
      RGB rgb_caps = hsv_to_rgb(hsv_caps);
      rgb_matrix_set_color(54, rgb_caps.r, rgb_caps.g, rgb_caps.b);
  }

  // 3) Function layer (layer 10) indicator on grave key (index 18)
  if (layer == _FL) {
      // White indicator for function layer on the grave key
      HSV hsv = { .h = 0, .s = 0, .v = 255 };
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(18, rgb.r, rgb.g, rgb.b);
      return false;
  }

  // 4) Layers 0-4 indicators
  // Display the active layer using a key in the number row
  // Each layer gets a different color with hue based on layer number
  if (layer <= 4) {
      uint8_t idx = 19 + layer; // Calculate which key to light (1-5 keys)
      HSV hsv = { .h = layer * 50, .s = 255, .v = 120 }; // Different hue for each layer
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(idx, rgb.r, rgb.g, rgb.b);
  }

  return false; // Allow other RGB effects to continue processing
}
#endif 
