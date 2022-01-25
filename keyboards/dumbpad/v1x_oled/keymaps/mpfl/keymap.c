/* Copyright 2020 imchipwood
 * Copyright 2021 Josh Johnson
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

#include "config.h"

#ifdef OLED_DRIVER_ENABLE
    #include "oled.c"
#endif

#define _FN 0
#define _NU 1
#define _NA 2
#define _ED 3
#define _EX 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            FUNCTION LAYER
    /-----------------------------------------------------`
    |             |   F13   |   F14   |   F15   |   F16   |
    |             |---------|---------|---------|---------|
    |             |   F17   |   F18   |   F19   |   F20   |
    |             |---------|---------|---------|---------|
    |             |   F21   |   F22   |   F23   |   F24   |
    |-------------|---------|---------|---------|---------|
    | Play Pause  |   _NU   |   _NA   |   _ED   |   _EX   |
    \-----------------------------------------------------'
    */
    [_FN] = LAYOUT(
                    KC_F13,     KC_F14,     KC_F15,      KC_F16,
                    KC_F17,     KC_F18,     KC_F19,      KC_F20,
                    KC_F21,     KC_F22,     KC_F23,      KC_F24,
        KC_MPLY,    TO(1),      TO(2),      TO(3),       TO(4)
    ),
    /*
            NUM LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |    -    |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    =    |
    |-------------|---------|---------|---------|---------|
    | Play Pause  |   _FN   |    0    |    .    |  ENTER  |
    \-----------------------------------------------------'
    */
    [_NU] = LAYOUT(
                    KC_7,      KC_8,    KC_9,             KC_KP_MINUS,
                    KC_4,      KC_5,    KC_6,             KC_KP_PLUS,
                    KC_1,      KC_2,    KC_3,             KC_EQL,
        _______,    TO(0),     KC_0,    LSFT_T(KC_DOT),   KC_ENTER
    ),
    /*
            NAV LAYER
    /-----------------------------------------------------`
    |             |  Home   |   Up    |  PgUp   |         |
    |             |---------|---------|---------|---------|
    |             |  Left   |         |  Right  |         |
    |             |---------|---------|---------|---------|
    |             |   End   |  Down   |  PgDn   |         |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |   _FN   |         |         |         |
    \-----------------------------------------------------'
    */
    [_NA] = LAYOUT(
                    KC_HOME,     KC_UP,       KC_PGUP,      KC_NO,
                    KC_LEFT,     KC_NO,       KC_RIGHT,     KC_NO,
                    KC_END,      KC_DOWN,     KC_PGDN,      KC_NO,
        _______,    TO(0),       KC_NO,       KC_NO,        KC_NO
    ),


    /*
            EDIT LAYER
    /-----------------------------------------------------`
    |             |         |         |         | Prt Scr |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |   CUT   |  COPY   |  PASTE  |         |
    |-------------|---------|---------|---------|---------|
    |             |   _FN   |  UNDO   |  REDO   |  SAVE   |
    \-----------------------------------------------------'
    */
    [_ED] = LAYOUT(
                    KC_NO,       KC_NO,       KC_NO,        KC_PSCR,
                    KC_NO,       KC_NO,       KC_NO,        KC_NO,
                    LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),   KC_NO,
        _______,    TO(0),       LCTL(KC_Z),  LCTL(KC_Y),   LCTL(KC_S)
    ),

    /*
            EXTRA LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |  Debug  |
    |             |---------|---------|---------|---------|
    |             |         |         |         | EEP Rst |
    |-------------|---------|---------|---------|---------|
    |             |   _FN   |         |         |         |
    \-----------------------------------------------------'
    */
    [_EX] = LAYOUT(
                    KC_NO,     KC_NO,     KC_NO,      RESET,
                    KC_NO,     KC_NO,     KC_NO,      DEBUG,
                    KC_NO,     KC_NO,     KC_NO,      EEP_RST,
        _______,    TO(0),     KC_NO,     KC_NO,      KC_NO
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    // Right encoder
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
    // Left encoder
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        oled_sleep_timer = timer_read32();
    }

    switch(keycode) {
    case TO(0):
    case TO(1):
    case TO(2):
    case TO(3):
    case TO(4):
        if (record->event.pressed) {
            isJumping  = true;
            showedJump = false;
        } else {
            isJumping = false;
        }
        break;
    }
    return true;
}
