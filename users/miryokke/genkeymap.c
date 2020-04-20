
#include QMK_KEYBOARD_H
#include "genkeymap.h"
#include "miryokke.h"

#define KC_NP KC_NO // key is not present
#define KC_NA KC_NO // present but not available for use
#define KC_NU KC_NO // available but not used

// non-KC_ keycodes
#define KC_RST RESET
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_miryokke(
        KC_ESC,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_BSPC,
        KC_TAB,            LCTL_T(KC_A),      LGUI_T(KC_S),      LALT_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LALT_T(KC_K),      LGUI_T(KC_L),      LCTL_T(KC_QUOT),   KC_SCLN,
        KC_LSFT,           KC_Z,              ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    RCTL_T(KC_SLSH),   KC_BSLS,
        KC_NP,             TO(COLEMAK),       KC_TRNS,           LT(MOUSE, KC_TAB), LT(NAV, KC_ENT),   LT(MEDIA, KC_ESC), LT(FUN, KC_DEL),   LT(NUM, KC_SPC),   LT(SYM, KC_BSPC),  KC_TRNS,           KC_TRNS,           KC_NP
    ),
    [COLEMAK] = LAYOUT_miryokke(
        KC_ESC,            KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,           KC_BSPC,
        KC_TAB,            LCTL_T(KC_A),      LGUI_T(KC_R),      LALT_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LALT_T(KC_E),      LGUI_T(KC_I),      LCTL_T(KC_O),      KC_SCLN,
        KC_LSFT,           KC_Z,              ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    RCTL_T(KC_SLSH),   KC_BSLS,
        KC_NP,             TO(QWERTY),        KC_TRNS,           LT(MOUSE, KC_TAB), LT(NAV, KC_ENT),   LT(MEDIA, KC_ESC), LT(FUN, KC_DEL),   LT(NUM, KC_SPC),   LT(SYM, KC_BSPC),  KC_TRNS,           KC_TRNS,           KC_NP
    ),
    [NAV] = LAYOUT_miryokke(
        KC_NA    , KC_RST   , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_AGIN  , KC_UNDO  , KC_CUT   , KC_COPY  , KC_PSTE  , KC_NU    ,
        KC_NA    , KC_LCTL  , KC_LGUI  , KC_LALT  , KC_LSFT  , KC_NA    , KC_CAPS  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_NU    ,
        KC_NA    , KC_NA    , KC_ALGR  , KC_NA    , KC_NA    , KC_NA    , KC_INS   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , KC_NU    ,
        KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_DEL   , KC_SPC   , KC_BSPC  , KC_NU    , KC_NU    , KC_NU    
    ),
    [MOUSE] = LAYOUT_miryokke(
        KC_NA    , KC_RST   , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    ,
        KC_NA    , KC_LCTL  , KC_LGUI  , KC_LALT  , KC_LSFT  , KC_NA    , KC_NU    , KC_MS_L  , KC_MS_D  , KC_MS_U  , KC_MS_R  , KC_NU    ,
        KC_NA    , KC_NA    , KC_ALGR  , KC_NA    , KC_NA    , KC_NA    , KC_NU    , KC_WH_L  , KC_WH_D  , KC_WH_U  , KC_WH_R  , KC_NU    ,
        KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_BTN3  , KC_BTN1  , KC_BTN2  , KC_NU    , KC_NU    , KC_NU    
    ),
    [MEDIA] = LAYOUT_miryokke(
        KC_NA    , KC_RST   , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_TOG   , KC_MOD   , KC_HUI   , KC_SAI   , KC_VAI   , KC_NU    ,
        KC_NA    , KC_LCTL  , KC_LGUI  , KC_LALT  , KC_LSFT  , KC_NA    , KC_NU    , KC_MPRV  , KC_VOLD  , KC_VOLU  , KC_MNXT  , KC_NU    ,
        KC_NA    , KC_NA    , KC_ALGR  , KC_NA    , KC_NA    , KC_NA    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    ,
        KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_MSTP  , KC_MPLY  , KC_MUTE  , KC_NU    , KC_NU    , KC_NU    
    ),
    [FUN] = LAYOUT_miryokke(
        KC_NU    , KC_F12   , KC_F7    , KC_F8    , KC_F9    , KC_PSCR  , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_RST   , KC_NA    ,
        KC_NU    , KC_F11   , KC_F4    , KC_F5    , KC_F6    , KC_SLCK  , KC_NA    , KC_LSFT  , KC_LALT  , KC_LGUI  , KC_LCTL  , KC_NA    ,
        KC_NU    , KC_F10   , KC_F1    , KC_F2    , KC_F3    , KC_PAUS  , KC_NA    , KC_NA    , KC_NA    , KC_ALGR  , KC_RCTL  , KC_NA    ,
        KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    
    ),
    [NUM] = LAYOUT_miryokke(
        KC_NU    , KC_NU    , KC_7     , KC_8     , KC_9     , KC_ASTR  , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_RST   , KC_NA    ,
        KC_NU    , KC_0     , KC_4     , KC_5     , KC_6     , KC_PLUS  , KC_NA    , KC_LSFT  , KC_LALT  , KC_LGUI  , KC_LCTL  , KC_NA    ,
        KC_NU    , KC_NU    , KC_1     , KC_2     , KC_3     , KC_EQL   , KC_NA    , KC_NA    , KC_NA    , KC_ALGR  , KC_RCTL  , KC_NA    ,
        KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_DOT   , KC_MINS  , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    
    ),
    [SYM] = LAYOUT_miryokke(
        KC_TILD  , KC_DLR   , KC_PERC  , KC_CIRC  , KC_LCBR  , KC_RCBR  , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_RST   , KC_NA    ,
        KC_GRV   , KC_EXLM  , KC_AT    , KC_HASH  , KC_LPRN  , KC_RPRN  , KC_NA    , KC_LSFT  , KC_LALT  , KC_LGUI  , KC_LCTL  , KC_NA    ,
        KC_NU    , KC_PERC  , KC_CIRC  , KC_AMPR  , KC_LBRC  , KC_RBRC  , KC_NA    , KC_NA    , KC_NA    , KC_ALGR  , KC_RCTL  , KC_NA    ,
        KC_NU    , KC_NU    , KC_NU    , KC_NU    , KC_UNDS  , KC_MINS  , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    , KC_NA    
    )
};
