/**
 * @file layers.h
 * @brief Layer definitions for keyboard firmware
 * 
 * This file defines the various keyboard layers used in the firmware.
 * Layers allow different key mappings to be activated, giving more
 * functionality with fewer physical keys.
 */

#pragma once

/**
 * @enum custom_layers
 * @brief Enumeration of all keyboard layers
 * 
 * The underscores don't mean anything - you can have a layer called STUFF or any other name.
 * Each layer gets a name for readability, which is then used in the keymap matrix.
 */
enum custom_layers {
    _BL = 0,    /**< Base Layer - Default layer (Colemak layout) */
    _QW = 1,    /**< QWERTY Layer - Standard QWERTY layout if needed */
    _RG = 2,    /**< RGB Layer - Controls for RGB lighting */
    _NM = 3,    /**< No Mod Layer - Similar to base but without modifiers */
    _NAV= 4,    /**< Navigation Layer - Arrow keys and text navigation */
    _FL = 10,   /**< Function Layer - F-keys, media controls, and special functions */
    _META = 11, /**< Meta Layer - Virtual desktop switching and application launching */
};