/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

extern keymap_config_t keymap_config;
/*
enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
*/
// BEGIN: Mine

// Fillers to make layering more clear
#define _______ KC_TRNS
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
// #define CTL_ENT   LCTL_T(KC_ENT)      // Tap for Enter, hold for Control
// #define OS_SHFT   OSM(MOD_LSFT)       // Sticky Shift
// #define SHIFT_S    MT(MOD_LSFT, KC_S) // Tap for s, hold for Shift
// #define SHIFT_L    MT(MOD_RSFT, KC_L) // Tap for l, hold for Shift
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
 * .-----------------------------------------------------------------------------------------------------------.
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | RETURN |
 * |-/HYPER-+-/NUMBR-+--------+-/SYMBL-+-/TEXT--+--------+--------+--------+--------+--------+-/NAV---+-/CTRL--|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT |
 * |-/(-----+-/SLECT-+--------+--------+--------+--------+--------+--------+--------+--------+--------+-/)-----|
 * | MOUSE  | LCTRL  | LALT   | LGUI   | BACKSP | BACKSP | SPACE  | SPACE  | LEFT   | DOWN   | UP     | RIGHT  |
 * '----------------------------------------------/CTRL----/CMND----/OPT---------------------------------------'
 */

[_QW] = LAYOUT_planck_grid( /* QWERTY */
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT,
    HPR_ESC, NM_KC_A, KC_S   , SY_KC_D, TX_KC_F, KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , NAV_SCL, KC_ENT ,
    KC_LSPO, TS_KC_Z, KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , FN_KC_M, KC_COMM, KC_DOT , KC_SLSH, KC_RSPC,  
    MO(_MS), KC_LCTL, KC_LALT, KC_LCMD, KC_BSPC, CTL_BSP, CMD_SPC, OPT_SPC, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
),

/* NUMBER
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | +      | 7      | 8      | 9      | *      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | ^^^^^^ | LALT   | LGUI   | .      |        | -      | 4      | 5      | 6      | /      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        | 1      | 2      | 3      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        | =      | 0      | .      |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_NM] = LAYOUT_planck_grid( /* NUMBER */
    _______, _______, _______, _______, _______, _______, KC_PPLS, KC_P7  , KC_P8  , KC_P9  , KC_PAST, _______,
    _______, _______, KC_LALT, KC_LCMD, KC_PDOT, _______, KC_PMNS, KC_P4  , KC_P5  , KC_P6  , KC_PSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  , _______, _______,
    _______, _______, _______, _______, _______, _______, KC_EQL , KC_0   , KC_PDOT, _______, _______, _______
),

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------.
 * | POWER  | F1     | F2     | F3     | F4     |        |        |        | VOL-   | MUTE   | VOL+   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | KEYBRD | F5     | F6     | F7     | F8     |        |        |        | PREV   | PLAY   | NEXT   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | BRGT+  | F9     | F10    | F11    | F12    |        |        | ^^^^^^ | PREV   | PLAY   | NEXT   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | BRGT-  |        |        |        | MSSN C |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_FN] = LAYOUT_planck_grid( /* FUNCTION */
    KC_SLEP, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, _______, _______, MVOL_DN, MVOL_MT, MVOL_UP, _______,
    MO(_KB), KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______,
    BRGT_UP, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______,
    BRGT_DN, _______, _______, _______, MSSN_CL, _______, _______, _______, _______, _______, _______, _______
),

// MISSING:
// %    KC_PERC
// #    KC_HASH     +
// |    KC_PIPE     +
// ~    KC_TILDE
// `    KC_GRV

/* SYMBOL
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | +      | "      | !      | @      | _      | &      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        | ^^^^^^ |        |        | -      | { / }  | ( / )  | [ / ]  | :      | *      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        | |      | \      | '      | < / >  | *      | ?      | $      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | #      | =      |        |        | CMMNT  | /      | ^      |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_SY] = LAYOUT_planck_grid( /* SYMBOL */
    _______, _______, _______, _______, _______, _______, KC_PLUS, KC_DQT , KC_EXLM, KC_AT  , KC_UNDS, KC_AMPR,
    _______, _______, _______, _______, _______, _______, KC_MINS, TD_CRLY, TD_PARN, TD_BRKT, KC_COLN, KC_ASTR,
    _______, _______, _______, _______, _______, KC_PIPE, KC_BSLS, KC_QUOT, TD_ANBK, KC_ASTR, KC_QUES, KC_DLR ,
    _______, _______, _______, _______, _______, KC_HASH, KC_EQL , _______, _______, TD_CMNT, KC_SLSH, KC_CIRC
),

/* NAVIGATION
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | SPACE1 | SPACE2 | SPACE3 | SPACE4 |        | HOME   | PG UP  |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | SPACE+ | APP+   | WIN+   | TAB+   | TAB2+  | LEFT   | DOWN   | UP     | RIGHT  | ^^^^^^ |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | SPACE- | APP-   | WIN-   | TAB-   | TAB2-  | END    | PG DN  |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_NV] = LAYOUT_planck_grid( /* NAVIGATION */
    _______, SPC_ONE, SPC_TWO, SPC_THR, SPC_FOR, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______,
    _______, _______, NXT_APP, NXT_WIN, NXT_TAB, NXT_ATB, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
    _______, _______, PRV_APP, PRV_WIN, PRV_TAB, PRV_ATB, KC_END , KC_PGDN, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* TEXT MANIPULATION
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        | ^^^^^^ |        | SHFT L | MV L D | MV L U | SHFT R | XXXXXX |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_TX] = LAYOUT_planck_grid( /* TEXT MANIPULATION */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, SHFT_LT, MV_L_DN, MV_L_UP, SHFT_RT, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* TEXT SELECTION
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | CHAR L | DOWN   | UP     | CHAR R |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        | WORD L | PG DWN | PG UP  | WORD R | XXXXXX |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | ^^^^^^ | CUT    | COPY   | PASTE  | HSTRY  | BGN LN | END DC | BGN DC | END LN |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        | SEL WD | SEL PG |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_TS] = LAYOUT_planck_grid( /* TEXT SELECTION */
    _______, _______, _______, _______, _______, _______, ESL_CHL, ESL_DWN, ESL_UP , ESL_CHR, _______, _______,
    _______, _______, _______, _______, _______, _______, ESL_WDL, ESL_PGD, ESL_PGU, ESL_WDR, XXXXXXX, _______,
    _______, _______, CUT    , COPY   , PASTE  , HSTRY  , ESL_LNB, ESL_DCE, ESL_DCB, ESL_LNE, _______, _______,
    _______, _______, _______, _______, _______, _______, SEL_WRD, SEL_PGH, _______, _______, _______, _______
),

/* MOUSE - POTENTIAL
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        | WHL L  | UP     | WHEEL- |        | ACCEL1 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        | ACCEL2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        | WHL R  |        | WHEEL+ |        | ACCEL3 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | ^^^^^^ | BTTN3  | BTTN2  | BTTN1  |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

/* MOUSE
 * .-----------------------------------------------------------------------------------------------------------.
 * |        |        | WHL L  | UP     | WHEEL- |        |        |        |        |        |        | ACCEL1 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        | LEFT   | DOWN   | RIGHT  |        |        |        |        |        |        | ACCEL2 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        | WHL R  |        | WHEEL+ |        |        |        |        |        |        | ACCEL3 |
 * |--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        | BTTN1  | BTTN2  | BTTN3  | ^^^^^^ |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_MS] = LAYOUT_planck_grid( /* MOUSE */
    _______, _______, KC_WH_L, KC_MS_U, KC_WH_D, _______, _______, _______, _______, _______, _______, KC_ACL0,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, KC_ACL1,
    _______, _______, KC_WH_R, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, KC_ACL2,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, _______
),

// Aud on   AU_ON
// Audoff   AU_OFF
// AU_TOG   Toggles Audio mode
// Mus on   MU_ON
// Musoff   MU_OFF
// MU_TOG   Toggles Music Mode
// MU_MOD   Cycles through the music modes

// This does not make sense

/* KEYBOARD
 * .-----------------------------------------------------------------------------------------|-RGB-CONTROLS----.
 * | RESET  |        |        |        |        |        |        |        |        |        | BRGT-  | BRGT+  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ^^^^^^ |        |        |        |        |        |        |        |        |        | SAT-   | SAT+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        | ^^^^^^ |        |        | HUE-   | HUE+   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        | MODE+  | PLAIN  | ON/OFF |
 * '-----------------------------------------------------------------------------------------------------------'
 */

[_KB] = LAYOUT_planck_grid( /* KEYBOARD */
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_HUI,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_M_P, RGB_TOG
)
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

// // BEGIN: DEFAULT
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//
// /* Qwerty
//  * ,-----------------------------------------------------------------------------------.
//  * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_QWERTY] = LAYOUT_planck_grid(
//     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
//     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
//     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
//     BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
// ),
//
// /* Colemak
//  * ,-----------------------------------------------------------------------------------.
//  * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_COLEMAK] = LAYOUT_planck_grid(
//     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
//     KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
//     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
//     BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
// ),
//
// /* Dvorak
//  * ,-----------------------------------------------------------------------------------.
//  * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_DVORAK] = LAYOUT_planck_grid(
//     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
//     KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
//     KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
//     BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
// ),
//
// /* Lower
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_LOWER] = LAYOUT_planck_grid(
//     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
//     _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
// ),
//
// /* Raise
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_RAISE] = LAYOUT_planck_grid(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),
//
// /* Plover layer (http://opensteno.org)
//  * ,-----------------------------------------------------------------------------------.
//  * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
//  * `-----------------------------------------------------------------------------------'
//  */
//
// [_PLOVER] = LAYOUT_planck_grid(
//     KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
//     XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
//     XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
//     EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
// ),
//
// /* Adjust (Lower + Raise)
//  * ,-----------------------------------------------------------------------------------.
//  * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      |      |      |      |      |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_ADJUST] = LAYOUT_planck_grid(
//     _______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
//     _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______,
//     _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// )
//
//
// };
/*
#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
*/