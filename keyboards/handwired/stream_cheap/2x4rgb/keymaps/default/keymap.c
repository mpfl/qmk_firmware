#include QMK_KEYBOARD_H
#include "config.h"

#define HSV_MYGREEN    85, 255, 255
#define HSV_MYRED      0, 255, 255
#define HSV_MYORANGE   21, 255, 255
#define HSV_MYWHITE    0, 0, 255

enum layers {
  _BASE = 0,
  _MUSIC = 1,
  _ZOOM = 2,
  _TEAMS = 3,
  _WEBEX = 4,
  _RGB = 5
};

/* Meeting keymaps
|-------------|--------------|--------------|------------|
| Mute/Unmute | Video on/off | Hand up/down | Prev layer |
|-------------|--------------|--------------|------------|
|             |              |              | Next layer |
|-------------|--------------|--------------|------------|
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, TO(5),
        RGB_TOG, KC_NO, RESET, TO(1)
    ),
    [_MUSIC] = LAYOUT(
        KC_AUDIO_VOL_DOWN,   KC_AUDIO_MUTE,       KC_AUDIO_VOL_UP,     TO(0),
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, TO(2)
    ),
    [_ZOOM] = LAYOUT(
        LALT(KC_A), LALT(KC_V), LALT(KC_Y), TO(1),
        KC_NO,      KC_NO,      KC_NO,      TO(3)
    ),
    [_TEAMS] = LAYOUT(
        LCTL(LSFT(KC_M)), LCTL(LSFT(KC_O)), LCTL(LSFT(KC_K)), TO(2),
        KC_NO,            KC_NO,            KC_NO,            TO(4)
    ),
    [_WEBEX] = LAYOUT(
        LCTL(KC_M), LCTL(LSFT(KC_V)), LCTL(LSFT(KC_R)), TO(3),
        KC_NO,      KC_NO,            KC_NO,            TO(5)
    ),
    [_RGB] = LAYOUT(
        RGB_HUI, RGB_SAI,        RGB_VAI,          TO(4),
        KC_LSFT, RGB_MODE_PLAIN, RGB_MODE_FORWARD, TO(0)
    )
};

const rgblight_segment_t PROGMEM rgb_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYGREEN}
);

const rgblight_segment_t PROGMEM rgb_music_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYORANGE}
);

const rgblight_segment_t PROGMEM rgb_zoom_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYRED}
);

const rgblight_segment_t PROGMEM rgb_teams_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYRED}
);

const rgblight_segment_t PROGMEM rgb_webex_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYRED}
);

const rgblight_segment_t PROGMEM rgb_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MYWHITE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_base_layer,
    rgb_music_layer,
    rgb_zoom_layer,
    rgb_teams_layer,
    rgb_webex_layer,
    rgb_rgb_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(_MUSIC, layer_state_cmp(state, _MUSIC));
    rgblight_set_layer_state(_ZOOM, layer_state_cmp(state, _ZOOM));
    rgblight_set_layer_state(_TEAMS, layer_state_cmp(state, _TEAMS));
    rgblight_set_layer_state(_WEBEX, layer_state_cmp(state, _WEBEX));
//    rgblight_set_layer_state(_RGB, layer_state_cmp(state, _RGB));
    return state;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TO(5):
            rgblight_blink_layer_repeat(_RGB, 200, 3);
            break;
    }
}
