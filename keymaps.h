/**
 * @file keymaps.h
 * @brief Keyboard keymap and layer definitions
 * 
 * This file defines the complete keyboard mapping structure, including:
 * - Layer definitions and their organization
 * - Key assignments for each layer
 * - Special key behaviors like tap dance
 * 
 * The keyboard uses multiple layers to extend functionality beyond what's physically available,
 * with the base layer using Colemak layout for improved ergonomics.
 */

#pragma once

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "layers.h"

/**
 * @enum tap_dance_codes
 * @brief Enumeration of tap dance actions
 * 
 * Tap Dance allows different actions when a key is tapped multiple times.
 */
enum {
  TD_ESC,  /**< Special escape key behavior - likely Escape on single tap, different action on double tap */
};

/**
 * @brief Complete keymap definition across all layers
 * 
 * Each layer provides a complete mapping of the keyboard matrix.
 * Layers are accessed through layer switching keycodes or layer-tap keys.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /**
   * Base Layer: Colemak Layout (_BL)
   * 
   * Primary typing layer with Colemak layout for improved ergonomics
   * Also includes function keys, navigation controls, and numpad access
   * 
   * Notable keys:
   * - CYC_S: Cycle sequence: semicolon (;) -> colon (:) -> hash (#) -> semicolon (;) -> ...
   * - META_LAYER: Activates the meta functionality layer
   */
[_BL] = LAYOUT(
  TD(TD_ESC), KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,     KC_1,     KC_2,     KC_3,    KC_4,    KC_5,   KC_6,   KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,     KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,   KC_J,   KC_L,     KC_U,     KC_Y,     CYC_S,   KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_BSPC,   CKC_A,    CKC_R,    CKC_S,   CKC_T,   CKC_D,   CKC_H,   CKC_N,    CKC_E,    CKC_I,    CKC_O,    KC_QUOT,  KC_ENT,             KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,    KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,   KC_K,   KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,    META_LAYER,  KC_LALT,           KC_SPC,                            KC_RWIN,  MO(_FL),  KC_APP,  KC_LEFT,  KC_DOWN,  KC_RGHT,                      KC_P0,    KC_PDOT),

  /**
   * QWERTY Layer (_QW)
   * 
   * Standard QWERTY layout for compatibility or when needed
   * Shares most modifier and special keys with the base layer
   * 
   * Notable keys:
   * - QK_LEAD: Activates Leader key functionality for custom key sequences
   */
[_QW] = LAYOUT(
  TD(TD_ESC), KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_LCAP,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 QK_LEAD,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT),

  /**
   * Function Layer (_FL)
   * 
   * Provides access to system controls, media keys, and special functions
   * Accessible from most other layers as a momentary toggle
   * 
   * Notable keys:
   * - QK_BOOT: Resets the keyboard for flashing new firmware
   * - TO/TG layer keys: Switches to or toggles specified layers
   * - RGB controls: Adjusts RGB lighting behavior
   * - E_PASS keys: Password/secrets entry functions
   * - SENTENCE_CASE_TOGGLE: Toggles automatic capitalization after periods
   * - PIN_ENTRY: Activates secure PIN entry mode
   */
[_FL] = LAYOUT(
  QK_BOOT,  KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPRV,  KC_MRWD,  KC_MPLY,  KC_MSTP,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,   _______,  _______,   _______,   _______, _______,
  _______,  TO(_BL),  TO(_QW),  TO(_RG),  TG(_NM),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,   _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             E_PASS4,  _______,  _______,
  SENTENCE_CASE_TOGGLE,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,             E_PASS1,  E_PASS2,  E_PASS3,  _______,  
  _______,  UC_WIN,   _______,                      _______,                                _______,  _______,  _______,  RGB_RMOD,   RGB_VAD,  _______,  PIN_ENTRY,  _______),

  /**
   * RGB Control Layer (_RG)
   * 
   * Dedicated layer for controlling RGB lighting effects
   * Provides comprehensive access to all RGB adjustment features
   * 
   * Key functions:
   * - RGB_TOG: Toggles RGB lighting on/off
   * - RGB_HUI/HUD: Increases/decreases hue
   * - RGB_SAI/SAD: Increases/decreases saturation
   * - RGB_VAI/VAD: Increases/decreases brightness
   * - RGB_M_*: Switches between different RGB animation modes
   */
[_RG] = LAYOUT(
  TD(TD_ESC),RGB_TOG, RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  RGB_M_P,  RGB_M_B,  RGB_M_SW, RGB_M_SN, _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,
  _______,  UC_WIN,   _______,                      _______,                                QK_LEAD,  MO(_FL),  _______,  _______,   _______,  _______,  _______,  _______),

  /**
   * No Mod Layer (_NM)
   * 
   * Similar to the base Colemak layer but with standard keys instead of custom ones
   * Useful for applications that behave differently with modifiers or custom keys
   * 
   * This layer uses standard key definitions without the custom behavior of CKC_* keys
   */
[_NM] = LAYOUT(
  TD(TD_ESC), KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,     KC_1,     KC_2,     KC_3,    KC_4,    KC_5,   KC_6,   KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,     KC_Q,     KC_W,     KC_F,    KC_P,    KC_G,   KC_J,   KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_CAPS,    KC_A,     KC_R,     KC_S,    KC_T,    KC_D,   KC_H,   KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,  KC_ENT,   KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,    KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,   KC_K,   KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,    KC_LGUI,  KC_LALT,           KC_SPC,                            KC_RALT,  MO(_FL),  TO(_BL),  KC_LEFT,  KC_DOWN,  KC_RGHT,                      KC_P0,    KC_PDOT),

/**
 * Navigation Layer (_NAV)
 * 
 * Provides enhanced text navigation and selection capabilities
 * Primarily used for cursor movement and text selection
 * 
 * Notable keys:
 * - SELECT_WORD: Selects the current word under cursor
 * - SELECT_LINE: Selects the entire current line
 * - SELECT_WORD_BACK: Selects the previous word
 * - Cursor movement keys in both home row and arrow key positions
 */
[_NAV] = LAYOUT(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  SELECT_WORD,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  SELECT_LINE,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_UP,    KC_DOWN,    KC_LEFT,  KC_RGHT, KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_RGHT,  KC_DOWN,    KC_UP,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, SELECT_WORD_BACK,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

/**
 * Meta Layer (_META)
 * 
 * Provides access to system-level operations and application launching
 * Used for virtual desktop switching and launching specific applications
 * 
 * Notable keys:
 * - VD_1 through VD_9: Switch to virtual desktops 1-9
 * - RUN_WT: Launch Windows Terminal
 * - RUN_FILES: Launch file explorer
 * - RUN_BROWSER: Launch web browser
 */
[_META] = LAYOUT(
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  VD_1,     VD_2,     VD_3,     VD_4,    VD_5,     VD_6,     VD_7,     VD_8,     VD_9,     KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RUN_WT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RUN_FILES,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, RUN_BROWSER,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
}; 