/**
 * @file on_smtd_action_impl.h
 * @brief Implementation of Smart Mod-Tap and Dual-function (SMTD) action handler
 * 
 * This file provides the implementation of the on_smtd_action function which defines
 * behavior for custom keycodes when used with the SMTD system. SMTD combines the
 * functionality of Mod-Tap and Layer-Tap keys with improved handling for repeated
 * taps, holds, and other advanced behaviors.
 * 
 * Usage: Include this file directly in keymap.c AFTER including sm_td.h
 * The primary function defined here (on_smtd_action) will be called by the
 * sm_td module when SMTD events occur.
 */

#pragma once

#include QMK_KEYBOARD_H
#include "features/sm_td.h"
#include "keymaps.h"
#include "custom_keycodes.h"

/**
 * @brief Handler for Smart Mod-Tap and Dual-function key events
 * 
 * This function is called by the SMTD system to handle different actions for
 * custom keycodes. It processes home row mods, layer-tap keys, and other
 * special behavior keys.
 * 
 * @param keycode   The custom keycode being processed
 * @param action    The current action being performed (SMTD_ACTION_TOUCH, etc.)
 * @param tap_count The number of consecutive taps for this key
 */
void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) 
{
    switch (keycode) 
    {
        /* 
         * Home Row Mods - Left Hand
         * SMTD_MT macro creates a mod-tap implementation where:
         * - Tap sends the base key (e.g., KC_A)
         * - Hold sends the modifier (e.g., KC_LEFT_GUI)
         */
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)  // A key: tap = 'a', hold = Left GUI (Win/Cmd)
        SMTD_MT(CKC_R, KC_R, KC_LEFT_ALT)  // R key: tap = 'r', hold = Left Alt
        SMTD_MT(CKC_S, KC_S, KC_LSFT)      // S key: tap = 's', hold = Left Shift
        SMTD_MT(CKC_T, KC_T, KC_LCTL)      // T key: tap = 't', hold = Left Control

        /* 
         * Home Row Mods - Right Hand
         * Mirroring the left hand modifiers for symmetry
         */
        SMTD_MT(CKC_N, KC_N, KC_RCTL)      // N key: tap = 'n', hold = Right Control
        SMTD_MT(CKC_E, KC_E, KC_RSFT)      // E key: tap = 'e', hold = Right Shift
        SMTD_MT(CKC_I, KC_I, KC_LALT)      // I key: tap = 'i', hold = Left Alt (common convention)
        SMTD_MT(CKC_O, KC_O, KC_RGUI)      // O key: tap = 'o', hold = Right GUI (Win/Cmd)

        /* 
         * Navigation Layer Keys
         * SMTD_LT macro creates a layer-tap implementation where:
         * - Tap sends the base key (e.g., KC_D)
         * - Hold temporarily activates the specified layer (e.g., _NAV)
         */
        SMTD_LT(CKC_D, KC_D, _NAV)         // D key: tap = 'd', hold = activate NAV layer
        SMTD_LT(CKC_H, KC_H, _NAV)         // H key: tap = 'h', hold = activate NAV layer

        /**
         * Symbol Cycling Key
         * 
         * Cycles through semicolon, colon, and hash symbols with repeated taps.
         * If a symbol is already entered, it will be deleted before typing the next one.
         * 
         * Cycle sequence: semicolon (;) -> colon (:) -> hash (#) -> semicolon (;) -> ...
         */
        case CYC_S:
        {
          switch (action) {
            case SMTD_ACTION_TOUCH:
              // If this isn't the first tap, delete the previous symbol
              if (tap_count > 0) {
                tap_code16(KC_BSPC);
              }
              
              // Type the next symbol in the cycle based on tap count
              switch (tap_count % 3) {
                case 0: tap_code16(KC_SEMICOLON);  break; // First tap = semicolon
                case 1: tap_code16(KC_COLON);      break; // Second tap = colon
                case 2: tap_code16(KC_HASH);       break; // Third tap = hash
              }
              break;
            default:
              break; // No action for other SMTD events
          }
          break;
        }
    }
} // end of on_smtd_action function 