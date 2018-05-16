/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "xd75.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

// Layer shorthand
#define _QW 0
#define _LW 1
#define _RS 2
#define _SY 3
#define _NV 4
#define _FN 5
#define _MS 6
#define _KB 7

// Custom
#define HPR_ESC   ALL_T(KC_ESC)       // Tap for Escape, hold for Hyper (Cmnd+Ctrl+Opt+Shift)
#define MEH_GRV   MEH_T(KC_GRV)       // Tap for Backtick, hold for Meh (Ctrl+Opt+Shift)
// Layers
#define NAV_SCL   LT(_NV, KC_SCLN)    // Tap for semicolon, hold for NAVIGATION layer
#define SY_KC_D   LT(_SY, KC_D)       // Tap for d, hold for SYMBOL layer
// Navigation
#define NXT_APP   LGUI(KC_TAB)        // MAC: switch to next application
#define PRV_APP   LGUI(S(KC_TAB))     // MAC: switch to prev application
#define NXT_WIN   LGUI(KC_GRV)        // MAC: switch to next window within an application
#define PRV_WIN   LGUI(S(KC_GRV))     // MAC: switch to prev window within an application
#define NXT_TAB   LCTL(KC_TAB)        // MAC: switch to next tab within an application
#define PRV_TAB   LCTL(S(KC_TAB))     // MAC: switch to prev tab within an application
#define NXT_ATB   LGUI(S(KC_RBRC))    // MAC: switch to next tab within an application (Shift+Cmnd+])
#define PRV_ATB   LGUI(S(KC_LBRC))    // MAC: switch to prev tab within an application (Shift+Cmnd+[)
#define SPC_ONE   LCTL(KC_1)          // MAC: switch to space 1
#define SPC_TWO   LCTL(KC_2)          // MAC: switch to space 2
#define SPC_THR   LCTL(KC_3)          // MAC: switch to space 3
#define SPC_FOR   LCTL(KC_4)          // MAC: switch to space 4
// Aliases
#define BRGT_UP   KC_PAUSE            // MAC: increase screen brightness
#define BRGT_DN   KC_SCROLLLOCK       // MAC: decrease screen brightness
#define MVOL_UP   KC__VOLUP           // MAC: increase volume
#define MVOL_DN   KC__VOLDOWN         // MAC: decrease volume
#define MVOL_MT   KC__MUTE            // MAC: mute volume

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | HOME   | \      | END    | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |-/MEH---+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | -      | PG UP  | =      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | [      | PG DN  | ]      | H      | J      | K      | L      | ;      | RETURN |
 * |-/HYPER-+--------+--------+-/SYMBL-+--------+--------+--------+--------+--------+--------+--------+--------+--------+-/NAV---+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | LOWER  | UP     | RAISE  | N      | M      | ,      | .      | /      | RSHIFT |
 * |-/(-----+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-/)-----|
 * | FN     | LCTRL  | LALT   | LGUI   | SPACE  | BACKSP | LEFT   | DOWN   | RIGHT  | RETURN | SPACE  | RGUI   | ENTER  | ????   | MOUSE  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
	
 [_QW] = { /* QWERTY */
  { MEH_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_HOME, KC_BSLS, KC_END , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC},
  { KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_MINS, KC_PGUP, KC_EQL , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT},
  { HPR_ESC, KC_A   , KC_S   , SY_KC_D, KC_F   , KC_G   , KC_LBRC, KC_PGDN, KC_RBRC, KC_H   , KC_J   , KC_K   , KC_L   , NAV_SCL, KC_ENT },
  { KC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , MO(_LW), KC_UP  , MO(_RS), KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC},  
  { MO(_FN), KC_LCTL, KC_LALT, KC_LCMD, KC_SPC , KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT , KC_SPC , KC_RCMD, KC_PENT, KC_PDOT, MO(_MS)},
 },

/* LOWERED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        | 7      | 8      | 9      | -      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        | =      | 4      | 5      | 6      | +      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        | ^^^^^^ |        |        |        | 1      | 2      | 3      | /      |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        | 0      | .      |        | *      |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_LW] = {   
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL , KC_P4  , KC_P5  , KC_P6  , KC_PPLS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  , KC_PSLS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0   , KC_PDOT, _______, KC_PAST, _______},
 },

/* RAISED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        | ^^^^^^ |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_RS] = { /* RAISED */ 
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 },

/* SYMBOL
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        | %      | ^      | &      | *      | -      | +      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        | +      | ->     | "      | !      | @      | _      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        | ^^^^^^ |        |        |        |        | -      |        | {      | (      | [      | :      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        | |      | \      | }      | )      | ]      | ?      | $      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        | #      | =      |        | <      | >      | /      |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_SY] = { /* SYMBOL */ 
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, _______, KC_DQT , KC_EXLM, KC_AT  , KC_UNDS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, _______, KC_LCBR, KC_LPRN, KC_LBRC, KC_COLN, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, KC_BSLS, KC_RCBR, KC_RPRN, KC_RBRC, KC_QUES, KC_DLR },
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_HASH, KC_EQL , _______, KC_LT  , KC_GT  , KC_SLSH, _______},
 },

/* NAVIGATION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | SPACE1 | SPACE2 | SPACE3 | SPACE4 |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | SPACE- | APP-   | WIN-   | TAB-   |        |        |        |        | HOME   | PG UP  |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | SPACE+ | APP+   | WIN+   | TAB+   | TAB2+  |        |        |        | LEFT   | DOWN   | UP     | RIGHT  | ^^^^^^ |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | SPACE- | APP-   | WIN-   | TAB-   | TAB2-  |        |        |        | END    | PG DN  |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | RGUI   | LALT   |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_NV] = { /* NAVIGATION */ 
  { _______, SPC_ONE, SPC_TWO, SPC_THR, SPC_FOR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, PRV_APP, PRV_WIN, PRV_TAB, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______},
  { _______, _______, NXT_APP, NXT_WIN, NXT_TAB, NXT_ATB, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______},
  { _______, _______, PRV_APP, PRV_WIN, PRV_TAB, PRV_ATB, _______, _______, _______, KC_END , KC_PGDN, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RCMD, KC_LALT, _______, _______, _______, _______},
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | POWER  | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | BRGT+  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | KEYBRD | F11    | F12    | F13    | F14    | F15    |        |        |        | F16    | F17    | F18    | F19    | F20    | BRGT-  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F21    | F22    | F23    | F24    |        |        |        |        | F21    | F22    | F23    | F24    |        | VOL+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | VOL-   | MUTE   | VOL+   |        |        |        |        |        | VOL-   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ^^^^^^ |        |        |        |        |        | PREV   | PLAY   | NEXT   |        |        |        |        |        | MUTE   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { KC_SLEP, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , BRGT_UP},
  { MO(_KB), KC_F11 , KC_F12 , KC_F13 , KC_F14 , KC_F15 , _______, _______, _______, KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , BRGT_DN},
  { _______, KC_F21 , KC_F22 , KC_F23 , KC_F24 , _______, _______, _______, _______, KC_F21 , KC_F22 , KC_F23 , KC_F24 , _______, MVOL_UP},
  { _______, _______, _______, _______, _______, _______, MVOL_DN, MVOL_MT, MVOL_UP, _______, _______, _______, _______, _______, MVOL_DN},
  { _______, _______, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______, _______, _______, MVOL_MT},
 },

/* MOUSE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | ACCEL1 | ACCEL2 | ACCEL3 |        |        |        |        |        |        |        |        |        |        | ACCEL1 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        | WHL L  | UP     | WHEEL- |        |        |        |        |        |        | UP     |        |        | ACCEL2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        | LEFT   | DOWN   | RIGHT  |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        | ACCEL3 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        | WHL R  |        | WHEEL+ |        | BTTN2  | BTTN 1 |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | BTTN1  | BTTN2  | BTTN3  | ^^^^^^ |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_MS] = {   
  { _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL0},
  { _______, _______, KC_WH_L, KC_MS_U, KC_WH_D, _______, _______, _______, _______, _______, _______, KC_MS_U, _______, _______, KC_ACL1},
  { _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_ACL2},
  { _______, _______, KC_WH_R, _______, KC_WH_U, _______, KC_BTN2, KC_BTN1, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, _______},
 },

/* KEYBOARD
 * .--------------------------------------------------------------------------------------------------------------------|-RGB-CONTROLS----.
 * | RESET  |        |        |        |        |        |        |        |        |        |        |        |        | MODE+  | BRGT+  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ^^^^^^ |        |        |        |        |        |        |        |        |        |        |        |        |        | BRGT-  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | SAT+   | HUE+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | SAT-   | HUE-   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | ^^^^^^ |        |        |        |        |        |        |        |        |        |        |        |        | PLAIN  | ON/OFF |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_KB] = {   
  { RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_VAI},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAI, RGB_HUI},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_HUD},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_P, RGB_TOG},
 }
};

const uint16_t PROGMEM fn_actions[] = {

};
