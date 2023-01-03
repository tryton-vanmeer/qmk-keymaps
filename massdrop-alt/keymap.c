#include QMK_KEYBOARD_H

#define MODS_SHIFT  (keyboard_report->mods & MOD_BIT(KC_LEFT_SHIFT) || keyboard_report->mods & MOD_BIT(KC_RIGHT_SHIFT))
#define MODS_CTRL  (keyboard_report->mods & MOD_BIT(KC_LEFT_CTRL) || keyboard_report->mods & MOD_BIT(KC_RIGHT_CTRL))
#define MODS_ALT  (keyboard_report->mods & MOD_BIT(KC_LEFT_ALT) || keyboard_report->mods & MOD_BIT(KC_RIGHT_ALT))

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    MD_BOOT,               //Restart into bootloader after hold timeout

    CMD_HOME,
    CMD_TERMINAL,
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        MO(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_MUTE, \
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, \
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_VOLU, \
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_VOLD, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),
    [2] = LAYOUT(
        KC_TILDE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UC(0x2014), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, CMD_TERMINAL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UC(0x2713), KC_TRNS, KC_TRNS, KC_APP, KC_TRNS, KC_TRNS, CMD_HOME, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK  \
    ),
    /*
    [X] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),
    */
};

//Setup Initial RGB
void matrix_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_WHITE);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {

        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;

        case CMD_HOME:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;

        case CMD_TERMINAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_LCTL("t")));
            }
            return false;

        case RGB_TOG:
            if (record->event.pressed) {
                if (MODS_CTRL) {
                    rgb_matrix_sethsv(HSV_RED);
                    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                }
                else if (MODS_ALT) {
                    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv(HSV_WHITE);
                }
                else if (MODS_SHIFT) {
                    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv(HSV_RED);
                }
                else {
                    rgblight_toggle();
                }
            }
            return false;

        default:
            return true; //Process all other keycodes normally
    }
}
