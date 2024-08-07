#include "quantum.h"
#include QMK_KEYBOARD_H

enum layers{
    BASE,
    FN,
    FN1,
};

enum ss_keys {
    SS_HOME,
};

enum unicode_names {
    EMDASH,
    LAMBDA,
    SML_LAMBDA,
    HOOKF,
    COPYLEFT,
    CHECKMARK,
    MIDDLEDOT,
};

const uint32_t unicode_map[] PROGMEM = {
    [EMDASH]     = 0x2014,  // —
    [LAMBDA]     = 0x039B,  // Λ
    [SML_LAMBDA] = 0x03BB,  // λ
    [HOOKF]      = 0x0192,  // ƒ
    [COPYLEFT]   = 0x1F12F, // 🄯
    [CHECKMARK]  = 0x2713,  // ✓
    [MIDDLEDOT]  = 0x00B7,  // ·
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_91_ansi(
        RGB_TOG,  KC_GRV,   KC_F1,    KC_F2,   KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_INS,   KC_DEL,   _______,
        KC_PSCR,  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  MO(FN),  KC_LGUI,  KC_LALT,         KC_SPC,                        KC_SPC,             KC_LALT,  MO(FN1), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [FN] = LAYOUT_91_ansi(
        _______,  _______,  KC_F13,    KC_F14,   KC_F15,    KC_F16,    KC_F17,     KC_F18,    KC_F19,    KC_F20,    KC_F21,    KC_F22,   KC_F23,     KC_F24,  _______,  _______,  _______,
        LALT(KC_PSCR),  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  UC(EMDASH),    _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  UC(LAMBDA), _______,  _______,   UC(HOOKF),  _______,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,            _______,  _______,  UC(COPYLEFT),  UC(CHECKMARK),   QK_BOOT,  _______,  _______,  _______,  UC(MIDDLEDOT),  SS_HOME,              _______,  KC_F15,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK
    ),
    [FN1] = LAYOUT_91_ansi(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  UC(SML_LAMBDA), _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            KC_END,
        _______,  _______,            _______,  _______,  _______,  _______,   QK_BOOT,  _______,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [FN]  = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [FN1]   = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
};

void matrix_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case SS_HOME:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;

        default:
            return true;
    }
}
