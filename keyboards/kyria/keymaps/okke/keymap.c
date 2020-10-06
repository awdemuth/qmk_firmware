/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 * Copyright 2020 Okke Formsma <okke@formsma.nl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;

enum layers {
    QWERTY = 0,
    COLEMAK,
    I3,
    NUMBERS,
    MOVE
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE
};

#define OK_A    MT(MOD_LCTL, KC_A)
#define OK_S    MT(MOD_LGUI, KC_S)
#define OK_D    MT(MOD_LALT, KC_D)
#define OK_F    MT(MOD_LSFT, KC_F)
#define OK_J    MT(MOD_RSFT, KC_J)
#define OK_K    MT(MOD_RALT, KC_K)
#define OK_L    MT(MOD_RGUI, KC_L)
#define OK_SCLN    MT(MOD_RCTL, KC_SCLN)
#define OK_V    LT(I3, KC_V)
#define OK_M    LT(I3, KC_M)


#define CM_A    MT(MOD_LCTL, KC_A)
#define CM_R    MT(MOD_LGUI, KC_R)
#define CM_S    MT(MOD_LALT, KC_S)
#define CM_T    MT(MOD_LSFT, KC_T)
#define CM_N    MT(MOD_RSFT, KC_N)
#define CM_E    MT(MOD_LALT, KC_E)
#define CM_I    MT(MOD_LGUI, KC_I)
#define CM_O    MT(MOD_LCTL, KC_O)
#define CM_D    LT(I3, KC_D)
#define CM_H    LT(I3, KC_H)


#define OK_GRV  MT(MOD_LCTL, KC_GRV)
#define OK_1    MT(MOD_LCTL, KC_1)
#define OK_2    MT(MOD_LGUI, KC_2)
#define OK_3    MT(MOD_LALT, KC_3)
#define OK_4    MT(MOD_LSFT, KC_4)
#define OK_7    MT(MOD_LSFT, KC_7)
#define OK_8    MT(MOD_LALT, KC_8)
#define OK_9    MT(MOD_LGUI, KC_9)
#define OK_0    MT(MOD_LCTL, KC_0)

#define OK_F5   MT(MOD_LCTL, KC_F5)
#define OK_F6   MT(MOD_LGUI, KC_F6)
#define OK_F7   MT(MOD_LALT, KC_F7)
#define OK_F8   MT(MOD_LSFT, KC_F8)

#define OK_QWE TO(QWERTY)
#define OK_COL TO(COLEMAK)

// THUMB KEYS
#define OK_TAB LT(NUMBERS, KC_TAB)
#define OK_SPC LT(NUMBERS, KC_SPC)
#define OK_ENT LT(MOVE, KC_ENT)
#define OK_BSPC LT(MOVE, KC_BSPC)
#define OK_SHFT OSM(MOD_LSFT)
#define OK_DEL LT(NUMBERS, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY/COLEMAK
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | esc    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |        |  ctrl|  gui | alt  | shift|      |                              |      | shift| alt  |  gui | ctrl |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |  \ |   |
 * |        |      |      |      |   i3 |      |             .  ,             |      |  i3  |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | COLE |      | tab  | spc  | ent  |  | bspc | shft | del  |      |      |
 *                        | QWER |      | numb | numb | move |  | move |      | numb |      |      |
 *                        `------`----------------------------  ----------------------------'------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
      KC_ESC,  OK_A,   OK_S,   OK_D,   OK_F,   KC_G,                                       KC_H,    OK_J,    OK_K,    OK_L,    OK_SCLN, KC_QUOT,
      _______, KC_Z,   KC_X,   KC_C,   OK_V,   KC_B,   _______, _______, _______, _______, KC_N,    OK_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                             OK_COL,   KC_NO,  OK_TAB, OK_SPC,  OK_ENT,  OK_BSPC, OK_SHFT, OK_DEL,  KC_NO, KC_NO
    ),
    [COLEMAK] = LAYOUT(
      _______, KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                                       KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, _______,
      _______, CM_A,   CM_R,   CM_S,   CM_T,   KC_G,                                       KC_M,    CM_N,    CM_E,    CM_I,    CM_O,    KC_SCLN,
      _______, KC_Z,   KC_X,   KC_C,   CM_D,   KC_V,   _______, _______, _______, _______, KC_K,    CM_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                             OK_QWE, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Numbers: numbers, specials
 * keep ,. for easy typing of numbers and IPs, keep backspace
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |  ^   |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |  -     |
 * |        |  ctrl|  gui | alt  | shift|      |                              |      | shift| alt  |  gui | ctrl |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  ~   |  `   |  _   |  [   |  ]   |      |      |  |      |      |  {   |  }   |  ,   |  .   |  +   |  =     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | tab  | spc  | ent  |  | bspc | shft | del  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [NUMBERS] = LAYOUT(
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, OK_1,    OK_2,   OK_3,    OK_4,    KC_5,                                        KC_6,    OK_7,    OK_8,    OK_9,    OK_0,    KC_MINS,
      _______, KC_TILD, KC_GRV, KC_UNDS, KC_LBRC, KC_RBRC, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_PLUS, KC_EQL,
                                _______, _______, _______, _______, _______,  KC_DEL, KC_BSPC, _______, _______, _______
    ),
/* i3 hotkeys - top row carries windows to workspace, home row navigates to workspace.*/
    [I3] = LAYOUT(
      _______, G(A(KC_1)), G(A(KC_2)), G(A(KC_3)), G(A(KC_4)), G(A(KC_5)),       G(A(KC_6)), G(A(KC_7)), G(A(KC_8)), G(A(KC_9)), G(A(KC_0)), _______,
      _______, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5),                                      G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * F-keys, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | VOL UP |  F1  |  F2  |  F3  |  F4  |      |                              | home | pgdn | pgup | end  |      | BRIU   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | VOL DN |  F5  |  F6  |  F7  |  F8  |      |                              | left | down | up   | right|      | BRID   |
 * |        |  ctrl|  gui | alt  | shift|      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | PL/PAUS|  F9  |  F10 |  F11 |  F12 | CAPS |      |      |  |      |      | mous4|      |      | mous5|      | PSCR   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | tab  | spc  | ent  |  | bspc | shft | del  |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * mous4 = back
 * mous5 = forward
 */
    [MOVE] = LAYOUT(
      KC_VOLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_BRIU,
      KC_VOLD, OK_F5,   OK_F6,   OK_F7,   OK_F8,   _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BRID,
      KC_MPLY, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS, _______, _______, _______, _______, KC_BTN4, _______, _______, KC_BTN5, _______, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CM_A:
        case CM_O:
        //case OK_A: //same as CM_A
        case OK_SCLN:
            return 100;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

bool is_keyboard_left(void);
void render_status_bar(void) {
    uint8_t modifiers = get_mods();
    if(is_keyboard_left()) {
        oled_write_P(PSTR("ctrl"), (modifiers & MOD_MASK_CTRL));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("gui"), (modifiers & MOD_MASK_GUI));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("alt"), (modifiers & MOD_MASK_ALT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("shift"), (modifiers & MOD_MASK_SHIFT));
    } else {
        oled_write_P(PSTR("shift"), (modifiers & MOD_MASK_SHIFT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("alt"), (modifiers & MOD_MASK_ALT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("gui"), (modifiers & MOD_MASK_GUI));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("ctrl"), (modifiers & MOD_MASK_CTRL));
    }
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("       Okke\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("qwerty\n"), false);
            break;
        case COLEMAK:
            oled_write_P(PSTR("colemak\n"), false);
            break;
        case NUMBERS:
            oled_write_P(PSTR("numbers\n"), false);
            break;
        case MOVE:
            oled_write_P(PSTR("func-move\n"), false);
            break;
        case I3:
            oled_write_P(PSTR("i3\n"), false);
            break;
        default:
            oled_write_P(PSTR("whut?\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
        render_status_bar();
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case QWERTY:
                // Move whole words. Hold shift to select while moving.
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            default:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
#endif
