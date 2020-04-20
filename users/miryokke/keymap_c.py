from itertools import chain


def parse_table(string):
    return list(
        list(cell.strip() for cell in row.split("|")) for row in string.strip().split("\n")
    )


#http://www.keyboard-layout-editor.com/#/gists/6fe00348d43dfaf3bc534c60df2e5fab
layers = {}
layers['full'] = {}
layers['left'] = {}
layers['right'] = {}
layers['hold'] = parse_table("""
 | RST  |      |      |      |      |      |      |      |      | RST  |
 | LCTL | LGUI | LALT | LSFT |      |      | LSFT | LALT | LGUI | LCTL |
 |      | ALGR |      |      |      |      |      |      | ALGR | RCTL |
 |      |      |mouse | nav  |media | fun  | num  | sym  |      |      |
""")

layers['full']['colemak'] = parse_table("""
ESC  |  Q    | W    | F    | P    | B    | J    | L    | U    | Y    | '   | BSPC
TAB  |  A    | R    | S    | T    | G    | M    | N    | E    | I    | O   | ;
LSFT |  Z    | X    | C    | D    | V    | K    | H    | ,    | .    | /   | \\
NP   |qwerty |      | TAB  | ENT  | ESC  | DEL  | SPC  | BSPC |      |     | NP
""")

layers['full']['qwerty'] = parse_table("""
ESC  |  Q    | W    | E    | R    | T    | Y    | U    | I    | O   | P   | BSPC
TAB  |  A    | S    | D    | F    | G    | H    | J    | K    | L   | '   | ;
LSFT |  Z    | X    | C    | V    | B    | N    | M    | ,    | .   | /   | \\
NP   |colemak|      | TAB  | ENT  | ESC  | DEL  | SPC  | BSPC |     |     | NP
""")

layers['right']['nav'] = parse_table("""
AGIN | UNDO | CUT  | COPY | PSTE |
CAPS | LEFT | DOWN | UP   | RGHT |
INS  | HOME | PGDN | PGUP | END  |
DEL  | SPC  | BSPC |      |      |
""")

layers['right']['mouse'] = parse_table("""
     |      |      |      |      |
     | MS_L | MS_D | MS_U | MS_R |
     | WH_L | WH_D | WH_U | WH_R |
BTN3 | BTN1 | BTN2 |      |      |
""")

layers['right']['media'] = parse_table("""
TOG  | MOD  | HUI  | SAI  | VAI  |
     | MPRV | VOLD | VOLU | MNXT |
     |      |      |      |      |
MSTP | MPLY | MUTE |      |      |
""")

layers['left']['num'] = parse_table(r"""
  |      | 7    | 8    | 9    | *
  | 0    | 4    | 5    | 6    | +
  |      | 1    | 2    | 3    | =
  |      |      |      | .    | -
""")
" `~!@#$%^&*"
layers['left']['sym'] = parse_table(r"""
 ~   |  $   | %    | ^    | {    | }
 `   |  !   | @    | #    | (    | )
     |  %   | ^    | &    | [    | ]
     |      |      |      | _    | -
""")

layers['left']['fun'] = parse_table("""
 | F12  | F7   | F8   | F9   | PSCR
 | F11  | F4   | F5   | F6   | SLCK
 | F10  | F1   | F2   | F3   | PAUS
 |      |      |      |      |
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

mods = set("LSFT LCTL LALT LGUI ALGR RCTL".split())


def layout(name):
    width = 19
    table = layers['full'][name]

    result = f'[{name.upper()}] = LAYOUT_miryokke(\n'
    for tap_row, hold_row in zip(table, layers['hold']):
        row = ' ' * 8
        for tap, hold in zip(tap_row, hold_row):
            if tap == '':
                code = 'KC_TRNS'
            elif tap in symbol_names:
                code = 'KC_' + symbol_names[tap]
            elif tap in layers['full'].keys():
                code = f'TO({tap.upper()})'
            else:
                code = 'KC_' + tap

            if hold in mods:
                code = hold + '_T(' + code + ')'
            elif hold in layers['left'] or hold in layers['right'] or hold in layers['full']:
                code = 'LT(' + hold.upper() + ', ' + code + ')'

            row += (code + ', ').ljust(width)
        result += row.rstrip(' ') + '\n'
    return result.rstrip(',\n') + '\n    )'


def layout_half(side, name):
    width = 9
    half_table = layers[side][name]
    length = len(half_table[0])
    rows = []
    for half_row, hold_row in zip(half_table, layers['hold']):
        cells = []
        hold_row_l, hold_row_r = hold_row[:length], hold_row[length:]
        for current_side, hold_row in ('left', hold_row_l), ('right', hold_row_r):
            if current_side == side:
                for half in half_row:
                    if half == '':
                        code = 'NU'
                    elif half in symbol_names:
                        code = symbol_names[half]
                    else:
                        code = half
                    cells.append(f'KC_{code}'.ljust(width))
            else:
                for hold in hold_row:
                    if hold == '' or hold != 'NP' and hold != 'RST' and hold not in mods:
                        code = 'NA'
                    else:
                        code = hold
                    cells.append(f'KC_{code}'.ljust(width))
        rows.append(cells)

    result = f'[{name.upper()}] = LAYOUT_miryokke(\n'
    result += ',\n'.join('        ' + ', '.join(cells) for cells in rows)
    result += '\n    )'
    return result


print(layout_half('right', 'nav'))
# print(layout_half('nsl', nsl))

keymap_c = f"""
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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{
    {layout('qwerty')},
    {layout('colemak')},
    {layout_half('right', 'nav')},
    {layout_half('right', 'mouse')},
    {layout_half('right', 'media')},
    {layout_half('left', 'fun')},
    {layout_half('left', 'num')},
    {layout_half('left', 'sym')}
}};
"""

layer_names = [layer.upper() for layer in chain(layers['full'], layers['left'], layers['right'])]
keymap_h = f"""
enum layers {{{', '.join(layer_names)}}};
"""
with open('genkeymap.c', 'w') as f:
    f.write(keymap_c)
with open('genkeymap.h', 'w') as f:
    f.write(keymap_h)
