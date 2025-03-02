// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "mousekey.h"

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_ctl_tab_active = false;
uint16_t ctl_tab_timer = 0;

enum layer_names {
    _BASE,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
    _L6,
    _L7,
    _L8,
    _L9
};

enum custom_keycodes {
  //JU_2 = SAFE_RANGE,
  JU_2 = QK_KB_0,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS,
  ALT_TAB,
  ALT_STB,
  CTL_TAB,
  CTL_STB
};

#define ALT_ESC LOPT_T(KC_ESC)
#define ML1_F10 LT(_L1, KC_F10)
#define ML2_F9 LT(_L2, KC_F9)
#define ML3_F2 LT(_L3, KC_F2)
#define WIN_D LGUI(KC_D)
#define WIN_V LGUI(KC_V)
#define LANG RALT(KC_GRV)
#define C_A_DEL LCA(KC_DEL)
#define ALT_PS RALT(KC_PSCR)
#define C_A_H LCA(KC_H)
#define V_DSK_R LGUI(LCTL(KC_RIGHT))
#define V_DSK_L LGUI(LCTL(KC_LEFT))


#define JU_LPRN LSFT(KC_8)
#define JU_RPRN LSFT(KC_9)
#define JU_LCBR LSFT(KC_RBRC)
#define JU_RCBR LSFT(KC_NUHS)
#define JU_AT KC_LBRC
#define JU_CIRC KC_EQL
#define JU_AMPR LSFT(KC_6)
#define JU_ASTR LSFT(KC_QUOT)
#define JU_COLN KC_QUOT
#define JU_PLUS LSFT(KC_SCLN)
#define JU_DQT LSFT(KC_2)
#define JU_TILD LSFT(KC_EQL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_8x7(
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          MS_UP  ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , JU_MINS,
        KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , MS_LEFT, XXXXXXX, MS_RGHT, KC_H   , KC_J   , KC_K   , KC_L   , JU_SCLN, JU_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , MS_BTN1, MS_DOWN, MS_BTN2, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, JU_EQL ,
        ALT_ESC,          KC_LGUI, ML1_F10, KC_DEL , KC_SPC ,          MO(_L4)         , KC_ENT , KC_BSPC, ML2_F9 , KC_PSCR,          ML3_F2
    ),
    [_L1] = LAYOUT_8x7(
        _______, XXXXXXX, KC_F1  , KC_F2  , KC_F3  , C_A_DEL,          MS_WHLU,          KC_1   , JU_2   , KC_3   , JU_0   , XXXXXXX, JU_TILD,
        _______, XXXXXXX, KC_F4  , KC_F5  , KC_F6  , C_A_H  , MS_WHLL, XXXXXXX, MS_WHLR, KC_4   , KC_5   , JU_6   , XXXXXXX, JU_COLN, JU_DQT ,
        _______, XXXXXXX, KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______, MS_WHLD, _______, JU_7   , JU_8   , JU_9   , KC_DOT , KC_QUES, JU_PLUS,
        _______,          _______, _______, _______, _______,          MS_BTN3         , _______, _______, LANG   , ALT_PS ,          _______
    ),
    [_L2] = LAYOUT_8x7(
        _______, XXXXXXX, XXXXXXX, JU_LCBR, JU_RCBR, V_DSK_L,          MS_WHLU,          KC_EXLM, JU_AT  , KC_HASH, JU_RPRN, XXXXXXX, JU_TILD,
        _______, XXXXXXX, XXXXXXX, JU_LBRC, JU_RBRC, V_DSK_R, MS_WHLL, XXXXXXX, MS_WHLR, KC_DLR , KC_PERC, JU_CIRC, XXXXXXX, JU_COLN, JU_GRV ,
        _______, XXXXXXX, XXXXXXX, JU_LPRN, JU_RPRN, XXXXXXX, _______, MS_WHLD, _______, JU_AMPR, JU_ASTR, JU_LPRN, KC_DOT , JU_BSLS, KC_PLUS,
        _______,          _______, LANG   , _______, _______,          MS_BTN3         , _______, _______, _______, ALT_PS ,          _______
    ),
    [_L3] = LAYOUT_8x7(
        XXXXXXX, UG_PREV, UG_NEXT, UG_VALU, UG_VALD, V_DSK_L,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        JU_CAPS, UG_HUEU, UG_HUED, XXXXXXX, XXXXXXX, V_DSK_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, UG_SATU, UG_SATD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG,          XXXXXXX, MS_BTN3, MS_BTN5, MS_BTN1,          XXXXXXX         , MS_BTN1, MS_BTN4, MS_BTN2, XXXXXXX,          _______
    ),
    [_L4] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          MS_WHLU,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MS_WHLL, XXXXXXX, MS_WHLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MS_BTN4, MS_WHLD, MS_BTN5, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, ALT_STB,          _______         , ALT_TAB, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    ),
    [_L5] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    ),
    [_L6] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    ),
    [_L7] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    ),
    [_L8] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    ),
    [_L9] = LAYOUT_8x7(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][2][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L1] =   { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_END, KC_HOME)},
    [_L2] =   { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLR, MS_WHLL)},
    [_L3] =   { ENCODER_CCW_CW(ALT_STB, ALT_TAB), ENCODER_CCW_CW(CTL_TAB ,CTL_STB )},
    [_L4] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L5] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L6] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L7] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L8] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    [_L9] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)}
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;

  switch (keycode) {
    case JU_2:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_2);
          unregister_code(KC_2);
        }
      }
      return false;
    case JU_6:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_EQL);
          unregister_code(KC_EQL);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_6);
          unregister_code(KC_6);
        }
      }
      return false;
    case JU_7:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_6);
          unregister_code(KC_6);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_7);
          unregister_code(KC_7);
        }
      }
      return false;
    case JU_8:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_8);
          unregister_code(KC_8);
        }
      }
      return false;
    case JU_9:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_8);
          unregister_code(KC_8);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_9);
          unregister_code(KC_9);
        }
      }
      return false;
    case JU_0:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_0);
          unregister_code(KC_0);
        }
      }
      return false;
    case JU_MINS:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_INT1);
          unregister_code(KC_INT1);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_MINS);
          unregister_code(KC_MINS);
        }
      }
      return false;
    case JU_EQL:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_MINS);
          unregister_code(KC_MINS);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_LBRC:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
        }
      }
      return false;
    case JU_RBRC:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_NUHS);
          unregister_code(KC_NUHS);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_NUHS);
          unregister_code(KC_NUHS);
        }
      }
      return false;
    case JU_BSLS:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_INT3);
          unregister_code(KC_INT3);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_INT1);
          unregister_code(KC_INT1);
        }
      }
      return false;
    case JU_SCLN:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
        }
      }
      return false;
    case JU_QUOT:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_2);
          unregister_code(KC_2);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_7);
          unregister_code(KC_7);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_GRV:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LSFT);
          register_code(KC_EQL);
          unregister_code(KC_EQL);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          unregister_code(KC_LSFT);
        }
      }
      return false;
    case JU_CAPS:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
        unregister_code(KC_LSFT);
      }
      return false;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
     case ALT_STB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
      break;
    case CTL_TAB:
      if (record->event.pressed) {
        if (!is_ctl_tab_active) {
          is_ctl_tab_active = true;
          register_code(KC_LCTL);
        }
        ctl_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case CTL_STB:
      if (record->event.pressed) {
        if (!is_ctl_tab_active) {
          is_ctl_tab_active = true;
          register_code(KC_LCTL);
        }
        ctl_tab_timer = timer_read();
        register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
     break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 800) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }

  if(is_ctl_tab_active){
    if (timer_elapsed(ctl_tab_timer) > 800) {
      unregister_code(KC_LCTL);
      is_ctl_tab_active = false;
    }
  }
}
