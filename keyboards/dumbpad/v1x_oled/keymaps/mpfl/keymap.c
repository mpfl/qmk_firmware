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

#ifdef OLED_DRIVER_ENABLE
    #include "oled.c"
#endif

#define _BASE 0
#define _NUM 1
#define _NAV 2
#define _EXTRA 3

// Fix cut copy paste

#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    F13  |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |-------------|---------|---------|---------|---------|
    | Play Pause  |  _NUM   |  _NAV   | _EXTRA  |         |
    \-----------------------------------------------------'
    */
    [_BASE] = LAYOUT(
                    KC_F13,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
                    _______,     _______,     _______,      _______,
        KC_MPLY,    TO(1),     TO(2),     TO(3),      _______
    ),
    /*
            NUM LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |    +    |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    -    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    =    |
    |-------------|---------|---------|---------|---------|
    | Play Pause  |  Lower  |    0    |    .    |  ENTER  |
    \-----------------------------------------------------'
    */
    [_NUM] = LAYOUT(
                    KC_7,      KC_8,    KC_9,             KC_KP_PLUS,
                    KC_4,      KC_5,    KC_6,             KC_KP_MINUS,
                    KC_1,      KC_2,    KC_3,             KC_EQL,
        KC_MPLY,    TO(0),     KC_0,    LSFT_T(KC_DOT),   KC_ENTER
    ),
    /*
            NAV LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    +    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |  Lower  |         |         |    =    |
    \-----------------------------------------------------'
    */
    [_NAV] = LAYOUT(
                    _______,     _______,     _______,      RESET,
                    _______,     _______,     _______,      KC_KP_PLUS,
                    _______,     _______,     _______,      KC_KP_MINUS,
        KC_LOCK,    _______,     _______,     _______,      KC_EQL
    ),


    /*
            EXTRA LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |-------------|---------|---------|---------|---------|
    |             |  Lower  |         |         |         |
    \-----------------------------------------------------'
    */
    [_EXTRA] = LAYOUT(
                    _______,     _______,     _______,      RESET,
                    _______,     _______,     _______,      _______,
                    KC_CUT,     KC_COPY,     KC_PASTE,      _______,
        _______,    _______,     _______,     _______,      _______
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
    switch(keycode) {
    case TO(0):
    case TO(1):
    case TO(2):
    case TO(3):
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
