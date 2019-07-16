/* Copyright 2019 Mathew Gacy
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
#define _NM 1
#define _FN 2
#define _SY 3
#define _NV 4
#define _TX 5
#define _TS 6
#define _MS 7
#define _KB 8

// Custom Aliases
#define HPR_ESC   ALL_T(KC_ESC)       // Tap for Escape, hold for Hyper (Cmnd+Ctrl+Opt+Shift)
#define MEH_GRV   MEH_T(KC_GRV)       // Tap for Backtick, hold for Meh (Ctrl+Opt+Shift)
#define CMD_SPC   LGUI_T(KC_SPC)      // Tap for Spacebar, hold for Command
#define OPT_SPC   LALT_T(KC_SPC)      // Tap for Spacebar, hold for Option
// #define CMD_EQL   LGUI_T(KC_EQL)      // Tap for Equal, hold for Command
// #define SFT_BSP   LCTL_T(KC_LSFT)     // Tap for Backspace, hold for Shift
#define CTL_BSP   LCTL_T(KC_BSPC)     // Tap for Backspace, hold for Control
//#define CTL_ENT   LCTL_T(KC_ENT)      // Tap for Enter, hold for Control
#define OS_SHFT   OSM(MOD_LSFT)       // Sticky Shift
// Layers
#define NAV_SCL   LT(_NV, KC_SCLN)    // Tap for semicolon, hold for NAVIGATION layer
#define NM_KC_A   LT(_NM, KC_A)       // Tap for a, hold for NUMBER layer
#define SY_KC_D   LT(_SY, KC_D)       // Tap for d, hold for SYMBOL layer
#define TX_KC_F   LT(_TX, KC_F)       // Tap for f, hold for TEXT MANIPULATION layer
#define FN_KC_M   LT(_FN, KC_M)       // Tap for m, hold for FUNCTION layer
#define TS_KC_Z   LT(_TS, KC_Z)       // Tap for z, hold for TEXT SELECTION layer
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
#define MSSN_CL   LCAG(KC_F3)         // MAC: Mission Control (Custom: Ctrl+Opt+Cmnd+F3)
#define BACK      LGUI(KC_LBRC)       // MAC: Back
#define FRWD      LGUI(KC_RBRC)       // MAC: Forward
// System
#define BRGT_UP   KC_PAUSE            // MAC: increase screen brightness
#define BRGT_DN   KC_SCROLLLOCK       // MAC: decrease screen brightness
#define MVOL_UP   KC__VOLUP           // MAC: increase volume
#define MVOL_DN   KC__VOLDOWN         // MAC: decrease volume
#define MVOL_MT   KC__MUTE            // MAC: mute volume
// Clipboard
#define CUT       LGUI(KC_X)          // MAC: Cut
#define COPY      LGUI(KC_C)          // MAC: Copy
#define PASTE     LGUI(KC_V)          // MAC: Paste
#define HSTRY     LALT(LGUI(KC_BSLS)) // LaunchBar: show clipboard history
// Text Manipulation
#define SHFT_LT   LGUI(KC_LBRC)       // Shift left
#define SHFT_RT   LGUI(KC_RBRC)       // Shift right
#define MV_L_UP   LALT(LGUI(KC_LBRC)) // Xcode: move line up
#define MV_L_DN   LALT(LGUI(KC_RBRC)) // Xcode: move line down
// Text Selection
#define SEL_WRD   LALT(KC_W)          // MAC: Select word
#define SEL_PGH   LALT(S(KC_S))       // MAC: Select paragraph
// - Shift + Arrow
#define ESL_CHL   S(KC_LEFT)          // MAC: Extend selection one character leftward
#define ESL_CHR   S(KC_RGHT)          // MAC: Extend selection one character rightward
#define ESL_UP    S(KC_UP)            // MAC: Extend selection upward
#define ESL_DWN   S(KC_DOWN)          // MAC: Extend selection downward
// - Option + Shift + Arrow
#define ESL_WDL   LALT(S(KC_LEFT))    // MAC: Extend selection one word leftward
#define ESL_WDR   LALT(S(KC_RGHT))    // MAC: Extend selection one word rightward
#define ESL_PGU   LALT(S(KC_UP))      // MAC: Extend selection to beginning of / to previous paragraph
#define ESL_PGD   LALT(S(KC_DOWN))    // MAC: Extend selection to end of / to next paragraph
// - Command + Shift + Arrow
#define ESL_LNB   LGUI(S(KC_LEFT))    // MAC: Extend selection to beginning of line
#define ESL_LNE   LGUI(S(KC_RGHT))    // MAC: Extend selection to end of line
#define ESL_DCB   LGUI(S(KC_UP))      // MAC: Extend selection to beginning of document
#define ESL_DCE   LGUI(S(KC_DOWN))    // MAC: Extend selection to end of document

// Tap Dance Declarations
enum {
  TD_CURLY = 0,
  TD_PAREN,
  TD_BRCKT,
  TD_ANGLE,
  TD_CMMNT
};

// Tap Dance Aliases
#define TD_CRLY   TD(TD_CURLY)        // Tap once for {, twice for }
#define TD_PARN   TD(TD_PAREN)        // Tap once for (, twice for )
#define TD_BRKT   TD(TD_BRCKT)        // Tap once for [, twice for ]
#define TD_ANBK   TD(TD_ANGLE)        // Tap once for <, twice for >
#define TD_CMNT   TD(TD_CMMNT)        // Tap once for /*, twice for */, thrice for """

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | -      | \      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |-/MEH---+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | INS    | HOME   | PG UP  | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | DEL    | END    | PG DN  | H      | J      | K      | L      | ;      | RETURN |
 * |-/HYPER-+-/NUMBR-+--------+-/SYMBL-+-/TEXT--+--------+--------+--------+--------+--------+--------+--------+--------+-/NAV---+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | NUMBR  | UP     | FN     | N      | M      | ,      | .      | /      | RSHIFT |
 * |-/(-----+-/SLECT-+--------+--------+--------+--------+--------+--------+--------+--------+-/FN----+--------+--------+--------+-/)-----|
 * | FN     | LCTRL  | LALT   | LGUI   | BACKSP | BACKSP | SSHIFT | DOWN   | RIGHT  | SPACE  | SPACE  | RGUI   | ENTER  | ????   | MOUSE  |
 * '----------------------------------------------/CTRL-------------------------------/CMND----/OPT---------------------------------------'
 */
	
 [_QW] = { /* QWERTY */
  { MEH_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_MINS, KC_BSLS, KC_EQL , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC},
  { KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_INS , KC_HOME, KC_PGUP, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT},
  { HPR_ESC, NM_KC_A, KC_S   , SY_KC_D, TX_KC_F, KC_G   , KC_DEL , KC_END , KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , NAV_SCL, KC_ENT },
  { KC_LSPO, TS_KC_Z, KC_X   , KC_C   , KC_V   , KC_B   , MO(_NM), KC_UP  , MO(_FN), KC_N   , FN_KC_M, KC_COMM, KC_DOT , KC_SLSH, KC_RSPC},  
  { MO(_FN), KC_LCTL, KC_LALT, KC_LCMD, KC_BSPC, CTL_BSP, OS_SHFT, KC_DOWN, KC_RGHT, CMD_SPC, OPT_SPC, KC_RCMD, KC_PENT, KC_PDOT, MO(_MS)},
 },

/* NUMBER
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        | +      | 7      | 8      | 9      | *      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | ^^^^^^ | LALT   | LGUI   | .      |        |        |        |        | -      | 4      | 5      | 6      | /      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        | 1      | 2      | 3      |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | =      | 0      | .      |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_NM] = { /* NUMBER */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PPLS, KC_P7  , KC_P8  , KC_P9  , KC_PAST, _______},
  { _______, _______, KC_LALT, KC_LCMD, KC_PDOT, _______, _______, _______, _______, KC_PMNS, KC_P4  , KC_P5  , KC_P6  , KC_PSLS, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  , _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL , KC_0   , KC_PDOT, _______, _______, _______},
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | POWER  | BRGT-  | BRGT+  | MSSN C |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | KEYBRD | F1     | F2     | F3     | F4     |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | F5     | F6     | F7     | F8     |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | F9     | F10    | F11    | F12    |        | VOL-   | MUTE   | VOL+   |        | ^^^^^^ |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        | PREV   | PLAY   | NEXT   |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = { /* FUNCTION */ 
  { KC_SLEP, BRGT_DN, BRGT_UP, MSSN_CL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { MO(_KB), KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, MVOL_DN, MVOL_MT, MVOL_UP, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______, _______, _______, _______},
 },

/* SYMBOL
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        | %      | ^      | &      | *      |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        | +      | "      | !      | @      | _      | &      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        | ^^^^^^ |        |        |        |        |        | -      | { / }  | ( / )  | [ / ]  | :      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        | |      | \      | '      | < / >  | *      | ?      | $      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        | #      | =      |        |        | CMMNT  | /      |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_SY] = { /* SYMBOL */ 
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_DQT , KC_EXLM, KC_AT  , KC_UNDS, KC_AMPR},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, TD_CRLY, TD_PARN, TD_BRKT, KC_COLN, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, KC_BSLS, KC_QUOT, TD_ANBK, KC_ASTR, KC_QUES, KC_DLR },
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_HASH, KC_EQL , _______, _______, TD_CMNT, KC_SLSH, _______},
 },

/* NAVIGATION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | SPACE1 | SPACE2 | SPACE3 | SPACE4 |        |        |        |        | HOME   | PG UP  | BACK   |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | SPACE+ | APP+   | WIN+   | TAB+   | TAB2+  |        |        |        | LEFT   | DOWN   | UP     | RIGHT  | ^^^^^^ |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | SPACE- | APP-   | WIN-   | TAB-   | TAB2-  |        |        |        | END    | PG DN  | FORWRD |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_NV] = { /* NAVIGATION */ 
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, SPC_ONE, SPC_TWO, SPC_THR, SPC_FOR, _______, _______, _______, _______, KC_HOME, KC_PGUP, BACK   , _______, _______, _______},
  { _______, _______, NXT_APP, NXT_WIN, NXT_TAB, NXT_ATB, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______},
  { _______, _______, PRV_APP, PRV_WIN, PRV_TAB, PRV_ATB, _______, _______, _______, KC_END , KC_PGDN, FRWD   , _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 },

/* TEXT MANIPULATION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        | ^^^^^^ |        |        |        |        | SHFT L | MV L D | MV L U | SHFT R | XXXXXX |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_TX] = { /* TEXT MANIPULATION */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, SHFT_LT, MV_L_DN, MV_L_UP, SHFT_RT, XXXXXXX, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 },

/* TEXT SELECTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        | CHAR L | DOWN   | UP     | CHAR R |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        | WORD L | PG DWN | PG UP  | WORD R | XXXXXX |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | ^^^^^^ | CUT    | COPY   | PASTE  | HSTRY  |        |        |        | BGN LN | END DC | BGN DC | END LN |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | SEL WD | SEL PG |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_TS] = { /* TEXT SELECTION */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, ESL_CHL, ESL_DWN, ESL_UP , ESL_CHR, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, ESL_WDL, ESL_PGD, ESL_PGU, ESL_WDR, XXXXXXX, _______},
  { _______, _______, CUT    , COPY   , PASTE  , HSTRY  , _______, _______, _______, ESL_LNB, ESL_DCE, ESL_DCB, ESL_LNE, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, SEL_WRD, SEL_PGH, _______, _______, _______, _______},
 },

/* MOUSE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | ACCEL1 | ACCEL2 | ACCEL3 |        |        |        |        |        |        |        |        |        |        | ACCEL1 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        | WHL L  | UP     | WHEEL- |        |        |        |        |        |        |        |        |        | ACCEL2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        | LEFT   | DOWN   | RIGHT  |        |        |        |        |        |        |        |        |        | ACCEL3 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        | WHL R  |        | WHEEL+ |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        | BTTN1  | BTTN2  | BTTN3  | ^^^^^^ |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_MS] = { /* MOUSE */
  { _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL0},
  { _______, _______, KC_WH_L, KC_MS_U, KC_WH_D, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL1},
  { _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ACL2},
  { _______, _______, KC_WH_R, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, _______},
 },

/* KEYBOARD
 * .--------------------------------------------------------------------------------------------------------------------|-RGB-CONTROLS----.
 * | RESET  |        |        |        |        |        |        |        |        |        |        |        |        | BRGT-  | BRGT+  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ^^^^^^ |        |        |        |        |        |        |        |        |        |        |        |        | HUE-   | HUE+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | SAT-   | SAT+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        | ^^^^^^ |        |        |        | MODE+  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        | PLAIN  | ON/OFF |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_KB] = { /* KEYBOARD */
  { RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_HUI},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_P, RGB_TOG},
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

// Tap Dance - Functions

// Tap Dance Comment
void dance_comment (qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        SEND_STRING ("/*");
        reset_tap_dance (state);
    case 2:
        SEND_STRING ("*/");
        reset_tap_dance(state);
    case 3:
        SEND_STRING ("\"\"\"");
        reset_tap_dance(state);
    }
}

// Tap Dance - Implementation
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for {, twice for }
  [TD_CURLY] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  // Tap once for (, twice for )
  [TD_PAREN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  // Tap once for [, twice for ]
  [TD_BRCKT] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  // Tap once for <, twice for >
  [TD_ANGLE] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
  // Tap once for /*, twice for */
  [TD_CMMNT] = ACTION_TAP_DANCE_FN(dance_comment)
};
