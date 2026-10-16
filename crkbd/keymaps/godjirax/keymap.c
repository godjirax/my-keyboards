/* Copyright 2019 Takuya Urakawa (dm9records.com)
 * Copyright 2026 Kevin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include QMK_KEYBOARD_H
#include "hid.h"
#include "keymap_french_mac_iso.h"
#include "split_common/transactions.h"

enum layers {
    _AZERTY,
    _FRENCH,
    _CODE,
    _NUMBERS,
    _LOWER,
    _ADJUST,
    _NUMBERS_NEW,
};

enum custom_keycodes {
    AZERTY = SAFE_RANGE,
    CODE_LAYER,
    FRENCH_LAYER,
    NUMBERS_LAYER,
    STAR_CODE,
    RGB_DIM,
    RGB_BRT,
};

#define M_CODE LT(_CODE, FR_M)
#define Q_CODE LT(_CODE, FR_Q)
#define S_NUMBERS_NEW LT(_NUMBERS_NEW, FR_S)
#define SPAC_FREN LT(_FRENCH, KC_SPC)
#define SPAC_NUM LT(_NUMBERS, KC_SPC)
#define ESC_LOWER LT(_LOWER, KC_ESC)
#define COMM_RCTL RCTL_T(FR_COMM)
#define ALT_TAB LALT(KC_TAB)
#define TH_DOT FR_ELLP

const uint16_t PROGMEM backspace_combo[] = {FR_V, FR_C, COMBO_END};

combo_t key_combos[] = {
    COMBO(backspace_combo, KC_BSPC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AZERTY] = LAYOUT_split_3x6_3(
        ESC_LOWER, FR_A, FR_W,          FR_E, FR_R, FR_T,  FR_Y, FR_U,      FR_I,    FR_O,    FR_P,    KC_BSPC,
        KC_TAB,  Q_CODE, S_NUMBERS_NEW, FR_D, FR_F, FR_G,  FR_H, FR_J,      FR_K,    FR_L,    M_CODE,  KC_ENT,
        KC_LSFT, FR_Z,   FR_X,          FR_C, FR_V, FR_B,  FR_N, COMM_RCTL, FR_SCLN, FR_COLN, FR_EQL,  _______,
                              KC_LALT, KC_LGUI,  SPAC_NUM,  SPAC_FREN, KC_RSFT, KC_RALT
    ),

    [_FRENCH] = LAYOUT_split_3x6_3(
        FR_AT,   FR_LAGR, _______, FR_LEAC, FR_LEGR, FR_DIAE,  FR_LUGR, KC_PGDN, KC_PGUP, FR_UNDS, FR_OCIR, _______,
        ALT_TAB, _______, _______, FR_DQUO, FR_QUOT, FR_CIRC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, FR_AT,   FR_EURO,
        _______, _______, FR_CCCE, FR_LCCE, _______, _______,  FR_ACUT, FR_EXLM, _______, FR_MINS, _______, _______,
                                    _______, _______, _______,  _______, _______, _______
    ),

    [_CODE] = LAYOUT_split_3x6_3(
        FR_TILD, FR_AMPR, FR_LABK, FR_LBRC, FR_RBRC, FR_DLR,  XXXXXXX, FR_ASTR, FR_QUOT, XXXXXXX, FR_UNDS, KC_DEL,
        KC_ESC,  FR_GRV,  FR_EQL,  FR_LPRN, FR_RPRN, FR_EXLM,  FR_COLN, FR_DOT,  FR_SLSH, XXXXXXX, FR_AT,   FR_DLR,
        _______, FR_PIPE, FR_RABK, FR_LCBR, FR_RCBR, FR_PERC,  FR_PLUS, FR_MINS, FR_HASH, TH_DOT,  FR_BSLS, _______,
                                    QK_MAKE, _______, _______,  _______, _______, _______
    ),

    [_NUMBERS] = LAYOUT_split_3x6_3(
        LGUI(LSFT(KC_4)), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ASTR, _______,
        KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_PLUS, FR_MINS, FR_COMM, FR_DOT,  FR_SLSH, _______,
                                    _______, _______, _______,  _______, _______, _______
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, RGB_DIM, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   RGB_BRT,    RGB_DIM,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
                              KC_BRID, KC_BRIU, LGUI(LSFT(KC_4)),  KC_VOLD, KC_VOLU, KC_MPLY
    ),

    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, AZERTY, CODE_LAYER, FRENCH_LAYER, NUMBERS_LAYER, _______,
        _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
                                    _______, _______, _______,  _______, _______, _______
    ),

    [_NUMBERS_NEW] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,  _______, FR_7, FR_8, FR_9, _______, _______,
        _______, _______, _______, _______, _______, _______,  _______, FR_4, FR_5, FR_6, _______, _______,
        _______, _______, _______, _______, _______, _______,  _______, FR_1, FR_2, FR_3, _______, _______,
                                    _______, _______, _______,  FR_0, FR_0, COMM_RCTL
    ),
};
// clang-format on

const uint8_t N_LAYERS = ARRAY_SIZE(keymaps);

static bool star_pressed;
static bool star_used;
static bool s_hold_used_layer_key;
static bool s_hold_settle_as_tap;
static bool gui_held;
static bool spac_num_held;
static bool ctrl_alt_chord;
static bool spac_num_swallowed;
static bool spac_num_suppress;
static uint16_t local_tap_count;
static matrix_row_t previous_matrix_rows[MATRIX_ROWS];

#ifdef RGB_MATRIX_ENABLE
typedef enum {
    EFFECT_LASER = 0,
    EFFECT_BURST = 1,
} effect_kind_t;

typedef struct {
    bool active;
    effect_kind_t kind;
    bool right_to_left;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint32_t start_time;
} laser_effect_t;

static laser_effect_t laser_effect;
static uint8_t burst_color_index;

#define LASER_DURATION_MS 220
#define LASER_WIDTH_X 18
#define BURST_DURATION_MS 320
#define BURST_WIDTH_X 22
#define LED_X_MAX 224
#define BURST_COLOR_COUNT 8

static const uint8_t burst_colors[BURST_COLOR_COUNT][3] = {
    {255,  40,  40}, // red
    {255, 120,   0}, // orange
    {255, 220,   0}, // yellow
    { 80, 255,  80}, // green
    {  0, 255, 220}, // cyan
    { 60, 140, 255}, // blue
    {170,  60, 255}, // purple
    {255,  40, 170}, // pink
};

static uint8_t scaled_brightness(uint8_t base) {
    return (uint16_t)base * rgb_matrix_get_val() / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
}

#ifdef SPLIT_KEYBOARD
typedef struct {
    uint8_t kind;
    bool right_to_left;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} laser_rpc_payload_t;
#endif

static void trigger_laser(bool right_to_left, uint8_t r, uint8_t g, uint8_t b) {
    laser_effect.active         = true;
    laser_effect.kind           = EFFECT_LASER;
    laser_effect.right_to_left  = right_to_left;
    laser_effect.r              = r;
    laser_effect.g              = g;
    laser_effect.b              = b;
    laser_effect.start_time     = timer_read32();
}

static void trigger_burst(uint8_t r, uint8_t g, uint8_t b) {
    laser_effect.active         = true;
    laser_effect.kind           = EFFECT_BURST;
    laser_effect.right_to_left  = false;
    laser_effect.r              = r;
    laser_effect.g              = g;
    laser_effect.b              = b;
    laser_effect.start_time     = timer_read32();
}

#ifdef SPLIT_KEYBOARD
static void rpc_laser_effect_slave(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    (void)target2initiator_buffer_size;
    (void)target2initiator_buffer;

    if (initiator2target_buffer_size != sizeof(laser_rpc_payload_t)) {
        return;
    }

    const laser_rpc_payload_t *payload = (const laser_rpc_payload_t *)initiator2target_buffer;
    if (payload->kind == EFFECT_BURST) {
        trigger_burst(payload->r, payload->g, payload->b);
    } else {
        trigger_laser(payload->right_to_left, payload->r, payload->g, payload->b);
    }
}
#endif

static void trigger_effect_synced(effect_kind_t kind, bool right_to_left, uint8_t r, uint8_t g, uint8_t b) {
    if (kind == EFFECT_BURST) {
        trigger_burst(r, g, b);
    } else {
        trigger_laser(right_to_left, r, g, b);
    }

#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        const laser_rpc_payload_t payload = {
            .kind = kind,
            .right_to_left = right_to_left,
            .r = r,
            .g = g,
            .b = b,
        };
        transaction_rpc_send(RPC_ID_LASER_EFFECT, sizeof(payload), &payload);
    }
#endif
}

static void trigger_next_burst_synced(void) {
    const uint8_t *color = burst_colors[burst_color_index];
    burst_color_index = (burst_color_index + 1) % BURST_COLOR_COUNT;
    trigger_effect_synced(EFFECT_BURST, false, color[0], color[1], color[2]);
}
#endif

static void update_local_tap_count_from_matrix(void) {
    const uint8_t split_row = MATRIX_ROWS / 2;
    const uint8_t start_row = is_keyboard_left() ? 0 : split_row;
    const uint8_t end_row   = is_keyboard_left() ? split_row : MATRIX_ROWS;

    for (uint8_t row = start_row; row < end_row; row++) {
        matrix_row_t current_row = matrix_get_row(row);
        matrix_row_t new_presses = current_row & ~previous_matrix_rows[row];

        while (new_presses) {
            local_tap_count++;
            new_presses &= (new_presses - 1);
        }

        previous_matrix_rows[row] = current_row;
    }
}

void keyboard_post_init_user(void) {
    local_tap_count = 0;
    memset(previous_matrix_rows, 0, sizeof(previous_matrix_rows));

#ifdef SPLIT_KEYBOARD
    transaction_register_rpc(RPC_ID_LASER_EFFECT, rpc_laser_effect_slave);
#endif

    if (default_layer_state != (1UL << _AZERTY)) {
        set_single_persistent_default_layer(_AZERTY);
    }
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _FRENCH:
            r = scaled_brightness(0);
            g = scaled_brightness(160);
            b = scaled_brightness(160);
            break;
        case _CODE:
            r = scaled_brightness(180);
            g = scaled_brightness(180);
            b = scaled_brightness(0);
            break;
        case _NUMBERS:
            r = scaled_brightness(0);
            g = scaled_brightness(0);
            b = scaled_brightness(180);
            break;
        case _LOWER:
            r = 0;
            g = 0;
            b = 0;
            break;
        case _ADJUST:
            r = scaled_brightness(180);
            g = scaled_brightness(0);
            b = scaled_brightness(0);
            break;
        case _NUMBERS_NEW:
            r = scaled_brightness(110);
            g = scaled_brightness(0);
            b = scaled_brightness(180);
            break;
        default:
            // _AZERTY default layer: LEDs off
            break;
    }

    rgb_matrix_set_color_all(r, g, b);

    if (laser_effect.active) {
        uint32_t elapsed = timer_elapsed32(laser_effect.start_time);

        if (laser_effect.kind == EFFECT_BURST) {
            if (elapsed >= BURST_DURATION_MS) {
                laser_effect.active = false;
                return false;
            }

            const uint16_t center_x = LED_X_MAX / 2;
            const uint16_t radius = (elapsed * center_x) / BURST_DURATION_MS;
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                int16_t distance = (int16_t)g_led_config.point[i].x - (int16_t)center_x;
                if (distance < 0) {
                    distance = -distance;
                }

                if (distance <= (int16_t)radius + BURST_WIDTH_X) {
                    rgb_matrix_set_color(i, scaled_brightness(laser_effect.r), scaled_brightness(laser_effect.g), scaled_brightness(laser_effect.b));
                }
            }
            return false;
        }

        if (elapsed >= LASER_DURATION_MS) {
            laser_effect.active = false;
            return false;
        }

        const uint16_t head = laser_effect.right_to_left ? (LED_X_MAX - ((elapsed * LED_X_MAX) / LASER_DURATION_MS)) : ((elapsed * LED_X_MAX) / LASER_DURATION_MS);

        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            int16_t distance = (int16_t)g_led_config.point[i].x - (int16_t)head;
            if (distance < 0) {
                distance = -distance;
            }

            if (distance <= LASER_WIDTH_X) {
                rgb_matrix_set_color(i, scaled_brightness(laser_effect.r), scaled_brightness(laser_effect.g), scaled_brightness(laser_effect.b));
            }
        }
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

static const char *layer_name(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _AZERTY:
            return "AZERTY";
        case _FRENCH:
            return "FRENCH";
        case _CODE:
            return "CODE";
        case _NUMBERS:
            return "NUMBERS";
        case _LOWER:
            return "LOWER";
        case _ADJUST:
            return "ADJUST";
        case _NUMBERS_NEW:
            return "NUM NEW";
        default:
            return "UNKNWN";
    }
}

bool oled_task_user(void) {
    update_local_tap_count_from_matrix();

    oled_write_ln_P(PSTR(" GODJIRAX"), false);
    oled_write_ln(is_keyboard_left() ? " LEFT  " : " RIGHT ", false);
    oled_write_P(PSTR("TAPS "), false);
    oled_write_ln(get_u16_str(local_tap_count, ' '), false);
    oled_write_P(PSTR("LAYER "), false);
    oled_write_ln(layer_name(), false);
    return false;
}
#endif

void matrix_scan_user(void) {
    // Tap counter updates are handled from oled_task_user().
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;
    (void)record;
    return TAPPING_TERM;
}

// Holding S opens _NUMBERS_NEW. Keys that layer actually remaps (digits, comma)
// stay as-is. Any other key types "s" first, then that key, and the layer is released.
static void handle_s_number_hold(uint16_t keycode, keyrecord_t *record) {
    if (keycode == S_NUMBERS_NEW) {
        if (record->event.pressed) {
            s_hold_used_layer_key = false;
            s_hold_settle_as_tap  = false;
        }
        return;
    }

    if (!record->event.pressed || !layer_state_is(_NUMBERS_NEW)) {
        return;
    }

    if (keymap_key_to_keycode(_NUMBERS_NEW, record->event.key) != KC_TRNS) {
        s_hold_used_layer_key = true;
        return;
    }

    if (s_hold_used_layer_key || s_hold_settle_as_tap) {
        return;
    }

    tap_code16(FR_S);
    s_hold_settle_as_tap = true;
}

// Holding Cmd + SPAC_NUM reports left Ctrl + left Alt for as long as both are held.
// Cmd is removed from the report, and the space layer-tap is not sent.
static void ctrl_alt_chord_on(void) {
    if (ctrl_alt_chord) {
        return;
    }
    ctrl_alt_chord = true;
    unregister_mods(MOD_BIT(KC_LGUI));
    register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    layer_off(_NUMBERS);
}

static void ctrl_alt_chord_off(void) {
    if (!ctrl_alt_chord) {
        return;
    }
    ctrl_alt_chord = false;
    unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    if (gui_held) {
        register_mods(MOD_BIT(KC_LGUI));
    }
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LGUI) {
        if (record->event.pressed) {
            gui_held = true;
            if (spac_num_held) {
                ctrl_alt_chord_on();
                if (!spac_num_swallowed) {
                    spac_num_suppress = true;
                }
                return false;
            }
        } else {
            gui_held = false;
            if (ctrl_alt_chord) {
                ctrl_alt_chord_off();
                return false;
            }
        }
        return true;
    }

    if (keycode == SPAC_NUM) {
        if (record->event.pressed) {
            spac_num_held = true;
            if (gui_held) {
                ctrl_alt_chord_on();
                spac_num_swallowed = true;
                return false;
            }
        } else {
            spac_num_held = false;
            if (spac_num_swallowed) {
                spac_num_swallowed = false;
                ctrl_alt_chord_off();
                return false;
            }
            if (ctrl_alt_chord) {
                ctrl_alt_chord_off();
            }
        }
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SPAC_NUM && spac_num_suppress) {
        if (!record->event.pressed) {
            spac_num_suppress = false;
        }
        return false;
    }

    handle_s_number_hold(keycode, record);

    send_event_to_hid(keycode, record->event);

#ifdef RGB_MATRIX_ENABLE
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_DIM:
                rgb_matrix_decrease_val();
                return false;
            case RGB_BRT:
                rgb_matrix_increase_val();
                return false;
        }
    }

    if (record->event.pressed && layer_state_is(_LOWER)) {
        switch (keycode) {
            case KC_BRID:
                trigger_effect_synced(EFFECT_LASER, true, 255, 255, 255);
                break;
            case KC_BRIU:
                trigger_effect_synced(EFFECT_LASER, false, 255, 255, 255);
                break;
            case KC_VOLD:
                trigger_effect_synced(EFFECT_LASER, true, 0, 255, 0);
                break;
            case KC_VOLU:
                trigger_effect_synced(EFFECT_LASER, false, 0, 255, 0);
                break;
            case KC_MPLY:
                trigger_next_burst_synced();
                break;
        }
    }
#endif

    if (star_pressed && keycode != STAR_CODE && record->event.pressed) {
        star_used = true;
    }

    switch (keycode) {
        case STAR_CODE:
            if (record->event.pressed) {
                star_pressed = true;
                star_used    = false;
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
                if (!star_used) {
                    tap_code16(FR_DLR);
                }
                star_pressed = false;
            }
            return false;

        case AZERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_AZERTY);
            }
            return false;

        case CODE_LAYER:
            record->event.pressed ? layer_on(_CODE) : layer_off(_CODE);
            return false;
        case FRENCH_LAYER:
            record->event.pressed ? layer_on(_FRENCH) : layer_off(_FRENCH);
            return false;
        case NUMBERS_LAYER:
            record->event.pressed ? layer_on(_NUMBERS) : layer_off(_NUMBERS);
            return false;
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;

    if (s_hold_settle_as_tap && record->event.pressed) {
        s_hold_settle_as_tap = false;
        layer_off(_NUMBERS_NEW);
    }
}
