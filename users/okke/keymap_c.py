def parse_table(string):
    return list(
        list(cell.strip() for cell in row.split("|")) for row in string.strip().split("\n")
    )

colemak_dkm_layout = parse_table("""
Q    | W    | F    | P    | B    | J    | L    | U    | Y    | '
A    | R    | S    | T    | G    | M    | N    | E    | I    | O
Z    | X    | C    | D    | V    | K    | H    | ,    | .    | /
NP   | NP   | ESC  | SPC  | TAB  | ENT  | BSPC | DEL  | NP   | NP
""")

qwerty_layout = parse_table("""
Q    | W    | E    | R    | T    | Y    | U    | I    | O    | P
A    | S    | D    | F    | G    | H    | J    | K    | L    | '
Z    | X    | C    | D    | V    | N    | M    | ,    | .    | /
NP   | NP   | ESC  | SPC  | TAB  | ENT  | BSPC | DEL  | NP   | NP
""")

hold_layout = parse_table("""
RST  |      |      |      |      |      |      |      |      | RST
LGUI | LALT | LCTL | LSFT |      |      | LSFT | LCTL | LALT | LGUI
     | ALGR |      |      |      |      |      |      | ALGR |
NP   | NP   | MEDR | NAVR | MOUR | NSSL | NSL  | FUNL | NP   | NP
""")

navr = parse_table("""
AGIN | UNDO | CUT  | COPY | PSTE
CAPS | LEFT | DOWN | UP   | RGHT
INS  | HOME | PGDN | PGUP | END
ENT  | BSPC | DEL  | NP   | NP
""")

mour = parse_table("""
     |      |      |      |
     | MS_L | MS_D | MS_U | MS_R
     | WH_L | WH_D | WH_U | WH_R
BTN3 | BTN1 | BTN2 | NP   | NP
""")

medr = parse_table("""
TOG  | MOD  | HUI  | SAI  | VAI
     | MPRV | VOLD | VOLU | MNXT
     |      |      |      |
MSTP | MPLY | MUTE | NP   | NP
""")

nsl = parse_table(r"""
[    | 7    | 8    | 9    | ]
'    | 4    | 5    | 6    | =
`    | 1    | 2    | 3    | \
NP   | NP   | .    | 0    | -
""")


funl = parse_table("""
F12  | F7   | F8   | F9   | PSCR
F11  | F4   | F5   | F6   | SLCK
F10  | F1   | F2   | F3   | PAUS
NP   | NP   | APP  | SPC  | TAB
""")

symbols_table = parse_table("""
`    | GRV  | ~    | TILD
-    | MINS | _    | UNDS
=    | EQL  | +    | PLUS
[    | LBRC | {    | LCBR
]    | RBRC | }    | RCBR
\    | BSLS | PIPE | PIPE
;    | SCLN | :    | COLN
'    | QUOT | DQUO | DQUO
,    | COMM | <    | LT
.    | DOT  | >    | GT
/    | SLSH | ?    | QUES
1    | 1    | !    | EXLM
2    | 2    | @    | AT
3    | 3    | #    | HASH
4    | 4    | $    | DLR
5    | 5    | %    | PERC
6    | 6    | ^    | CIRC
7    | 7    | &    | AMPR
8    | 8    | *    | ASTR
9    | 9    | (    | LPRN
0    | 0    | )    | RPRN
""")

symbol_names = {}
shifted_symbol_names = {}
for symbol, name, shifted_symbol, shifted_name in symbols_table:
    symbol_names[symbol] = name
    symbol_names[shifted_symbol] = shifted_name
    shifted_symbol_names[symbol] = shifted_name

mods = set("LSFT LCTL LALT LGUI ALGR".split())

def layout(name, table):
    width = 19

    result = f'[' + name + '] = LAYOUT_miryokke(\n'
    for tap_row, hold_row in zip(table, hold_layout):
        row = ' '*8
        for tap, hold in zip(tap_row, hold_row):
            if tap == '':
                code = 'NU'
            elif tap in symbol_names:
                code = symbol_names[tap]
            else:
                code = tap
            code = 'KC_' + code

            if hold in mods:
                code = hold + '_T(' + code + ')'
            elif hold not in ('', 'NP', 'RST'):
                code = 'LT(' + hold + ', ' + code + ')'

            row += (code + ', ').ljust(width)
        result += row.rstrip(' ') + '\n'
    return result.rstrip(', ') + '    )'

def layout_half(name, half_table, shift=False):
    width = 9

    length = len(half_table[0])
    mode = name[-1:].lower()

    result = '[' + name + '] = LAYOUT_miryokke(\n'
    for half_row, hold_row in zip(half_table, hold_layout):
      row = ' '*8
      hold_row_l, hold_row_r = hold_row[:length], hold_row[length:]
      for lr, hold_row_lr in ('l', hold_row_l), ('r', hold_row_r):
        if lr == mode:
          for half in half_row:
            if half == '':
              code = 'NU'
            elif shift == "true" and half in shifted_symbol_names:
              code = shifted_symbol_names[half]
            elif half in symbol_names:
              code = symbol_names[half]
            else:
              code = half
            row += ('KC_' + code + ', ').ljust(width)
        else:
          for hold in hold_row_lr:
            if hold == '' or hold != 'NP' and hold != 'RST' and hold not in mods:
              code = 'NA'
            else:
              code = hold
            row += ('KC_' + code + ', ').ljust(width)
      result += row.rstrip(' ') + '\n'
    return result.rstrip('\n, ') + '\n    )'

# print(layout_half('navr', navr))
# print(layout_half('nsl', nsl))

layers = "MEDR NAVR MOUR NSSL NSL FUNL".split()

keymap_c = f"""
#include QMK_KEYBOARD_H

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
enum layers {{ QWERTY, BASE, {', '.join(layers)} }}'

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{
    {layout('QWERTY', qwerty_layout)}
    {layout('COLEMAK', colemak_dkm_layout)}
    {layout_half("NAVR", navr)}
    {layout_half("MOUR", mour)}
    {layout_half("MEDR", medr)}
    {layout_half("FUNL", funl)}
    {layout_half("NSL", nsl)}
    {layout_half("NSSL", nsl, shift=True)}
}};
"""
print(keymap_c)

"""
*** ortho_4x12

#define LAYOUT_miryokke(\
K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,\
K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,\
K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,\
N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39\
)\
LAYOUT_ortho_4x12(\
KC_NO, K01,   K02,   K03,   K04,   KC_NO, KC_NO, K05,   K06,   K07,   K08,   KC_NO,\
K00,   K11,   K12,   K13,   K14,   KC_NO, KC_NO, K15,   K16,   K17,   K18,   K09,\
K10,   K21,   K22,   K23,   K24,   KC_NO, KC_NO, K25,   K26,   K27,   K28,   K19,\
K20,   KC_NO, KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   KC_NO, KC_NO, K29\
)

*** crkbd

#define LAYOUT_miryokke( \
       K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT( \
KC_NO, K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   KC_NO, \
KC_NO, K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   KC_NO, \
KC_NO, K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   KC_NO, \
                     K32,   K33,   K34,   K35,   K36,   K37 \
)

*** kyria

#define LAYOUT_miryokke( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
  K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
  K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
  N30, N31, K32, K33, K34, K35, K36, K37, N38, N39 \
) \
LAYOUT( \
    KC_NO, K00, K01, K02, K03, K04,                     K05, K06, K07, K08, K09, KC_NO, \
    KC_NO, K10, K11, K12, K13, K14,                     K15, K16, K17, K18, K19, KC_NO, \
    KC_NO, K20, K21, K22, K23, K24, KC_NO, KC_NO, KC_NO, KC_NO, K25, K26, K27, K28, K29, \
                    N30, N31, K32, K33, K34, K35, K36, K37, N38, N39 \
)
"""
