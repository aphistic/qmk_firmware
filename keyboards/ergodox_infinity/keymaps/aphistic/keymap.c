// See https://github.com/bbcmicrobit/micropython/issues/514#issuecomment-404759614
// for build issues on Ubuntu 18.04 LTS

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE       0 // default layer
#define MACOS_BASE 1
#define LAYER1     10 // layer 1
#define LAYER2     11 // layer 2

#define KC_CA(KC) LALT(LCTL(KC))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  SEND_BASE,
  SEND_MACOS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
  // left hand
  KC_ESC,     KC_1,         KC_2,    KC_3,    KC_4,    KC_5, KC_6,
  KC_TAB,     KC_Q,         KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC,
  KC_LCTL,    KC_A,         KC_S,    KC_D,    KC_F,    KC_G, /*NONE*/
  KC_LSFT,    KC_Z,         KC_X,    KC_C,    KC_V,    KC_B, KC_EQL,
  KC_GRV,     KC_INS,       XXXXXXX, XXXXXXX, KC_LALT,

  XXXXXXX,            DF(MACOS_BASE),
  /*NONE*/            XXXXXXX,
  KC_SPC, MO(LAYER1), KC_LGUI,

  // right hand
  KC_6,    KC_7,    KC_8,  KC_9,     KC_0,    KC_MINS,  KC_BSPC,
  KC_RBRC, KC_Y,    KC_U,  KC_I,     KC_O,    KC_P,     KC_BSLS,
  /*NONE*/ KC_H,    KC_J,  KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
  KC_EQL,  KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RCTL,

  TG(LAYER2), SEND_BASE,
  XXXXXXX,    /*NONE*/
  KC_LGUI,    MO(LAYER1), KC_ENT
),
[MACOS_BASE] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
    KC_ESC,     KC_1,         KC_2,    KC_3,    KC_4,    KC_5, KC_6,
    KC_TAB,     KC_Q,         KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC,
    KC_LGUI,    KC_A,         KC_S,    KC_D,    KC_F,    KC_G, /*NONE*/
    KC_LSFT,    KC_Z,         KC_X,    KC_C,    KC_V,    KC_B, KC_EQL,
    KC_GRV,     KC_INS,       XXXXXXX, XXXXXXX, KC_LALT,

    DF(BASE),           DF(BASE),
    /*NONE*/            XXXXXXX,
    KC_SPC, MO(LAYER1), LCTL(KC_LGUI),

    // right hand
    KC_6,    KC_7,    KC_8,  KC_9,     KC_0,    KC_MINS,  KC_BSPC,
    KC_RBRC, KC_Y,    KC_U,  KC_I,     KC_O,    KC_P,     KC_BSLS,
    /*NONE*/ KC_H,    KC_J,  KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
    KC_EQL,  KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
    KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RCTL,

    TG(LAYER2),    SEND_MACOS,
    XXXXXXX,       /*NONE*/
    RCTL(KC_RGUI), MO(LAYER1), KC_ENT
),
[LAYER1] = LAYOUT_ergodox(
  // left hand
  _______, KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,
  _______, KC_CA(KC_Q), KC_CA(KC_W), KC_CA(KC_E), KC_CA(KC_R), KC_CA(KC_T), _______,
  _______, _______, _______, _______, _______, _______,     /*NONE*/
  _______, _______, _______, _______, _______, _______,     _______,
  _______, _______, _______, _______, _______,

  _______, _______,
  /*NONE*/ _______,
  _______, _______, _______,

  // right hand
  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_DEL,
  _______, _______, _______, _______, _______, _______, _______,
  /*NONE*/ _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,

  _______, _______,
  _______, /*NONE*/
  _______, _______, _______
),
[LAYER2] = LAYOUT_ergodox(
  // left hand
  RESET,   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, /*NONE*/
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,

  _______, _______,
  /*NONE*/ _______,
  _______, _______, _______,

  // right hand
  _______, _______, _______, _______, _______, _______, RESET,
  _______, _______, _______, _______, _______, _______, _______,
  /*NONE*/ _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,

  _______, _______,
  _______, /*NONE*/
  _______, _______, _______
),
};

const uint16_t PROGMEM fn_actions[] = {
  //    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SEND_BASE:
      if (!record->event.pressed) {
          SEND_STRING("layer: base");
      }
      break;
  case SEND_MACOS:
      if (!record->event.pressed) {
          SEND_STRING("layer: macos");
      }
      break;

  // dynamically generate these.
  case EPRM:
      if (record->event.pressed) {
      eeconfig_init();
      }
      return false;
      break;
  case VRSN:
      if (record->event.pressed) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  case RGB_SLD:
      if (record->event.pressed) {
      #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
      #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
