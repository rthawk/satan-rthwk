#include "satan.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _SL 2
#define _CUSTOM 3
#define ENTERDUAL LT(_SL, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer */
[_BL] = KEYMAP_ANSI(
  F(0),      KC_1,   GUI_T(KC_2),   CTL_T(KC_3),  KC_4,    KC_5,   KC_6,   KC_7,   CTL_T(KC_8),  GUI_T(KC_9),    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC, \
  KC_TAB,    KC_Q,   KC_W,   KC_E,        KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,         KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS, \
  KC_LCTL,   KC_A,   KC_S,   KC_D,        KC_F,   KC_G,   KC_H,   KC_J,   KC_K,         KC_L,    KC_SCLN, KC_QUOT,            ENTERDUAL,  \
  KC_LSFT,   KC_Z,   KC_X,   KC_C,        KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,      KC_DOT,  KC_SLSH,                     KC_RSFT, \
  MO(_FL), KC_LGUI,KC_LALT,                          KC_SPC,                            KC_RALT, MO(_SL),  KC_RGUI,  KC_RCTL),

  /* Keymap _FL: Function Layer */
[_FL] = KEYMAP_ANSI(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,          KC_F8,        KC_F9,          KC_F10,   KC_F11,  KC_F12,  KC_DEL,  \
  KC_TRNS,  KC_ESC,   KC_BTN2,  KC_END,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PGUP,        KC_INS,       KC_HOME,        KC_HOME,   KC_MPRV, KC_MNXT, KC_MPLY, \
  KC_TRNS,  KC_HOME,  KC_BTN2,  KC_PGDN,   KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_DOWN,        KC_UP,        KC_RIGHT,       KC_TRNS,   KC_TRNS,  KC_TRNS, \
  KC_TRNS,  KC_TRNS,  KC_TRNS,  BL_DEC,    BL_TOGG,  BL_INC,   KC_END,   KC_ENT,         KC_BSPC,      LCTL(KC_A),     KC_TRNS,   KC_TRNS,   \
  KC_TRNS,  KC_TRNS,  F(9),                                    KC_BTN1,                                                KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),

[_CUSTOM] = KEYMAP_ANSI(
  F(0),      KC_1  ,  KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,     KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC, \
  KC_TAB,    BL_DEC,  BL_TOGG, BL_INC,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_LPRN,  KC_RPRN,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS, \
  KC_LCTL,   KC_A  ,  KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_LBRC,  KC_RBRC,    KC_SCLN, KC_QUOT,            ENTERDUAL,  \
  KC_LSFT,   KC_Z  ,  KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_LCBR,  KC_RCBR,  KC_SLSH,                     KC_RSFT, \
  MO(_FL), KC_LGUI,KC_LALT,                          KC_SPC,                            KC_RALT, MO(_SL),  KC_RGUI,  KC_RCTL),

[_SL] = KEYMAP_ANSI(
  KC_GRV,  KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,  \
  KC_TRNS, KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_EQL , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, \
  KC_TRNS, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_MINS, KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,          KC_TRNS, \
  KC_TRNS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, BL_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,   \
  KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

enum function_id {
    SHIFT_ESC,
    #ifdef RGBLIGHT_ENABLE
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL
    #endif
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
  #ifdef RGBLIGHT_ENABLE
  [1]  = ACTION_FUNCTION(RGBLED_TOGGLE),
  [2]  = ACTION_FUNCTION(RGBLED_STEP_MODE),
  [3]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
  [4]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
  [5]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
  [6]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
  [7]  = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
  [8]  = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
  #endif
  [9]  = ACTION_LAYER_MODS(2, MOD_LSFT)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    //led operations
    #ifdef RGBLIGHT_ENABLE
    case RGBLED_TOGGLE:
      if (record->event.pressed) {
        rgblight_toggle();
      }
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
      }
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
      }
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
      }
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
      }
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        rgblight_increase_val();
      }
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        rgblight_decrease_val();
      }
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        rgblight_step();
      }
      break;
    #endif
  }
}
