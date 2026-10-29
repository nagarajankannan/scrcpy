#include "common.h"

#include <assert.h>

#include "mac_keys.h"

static void test_cmd_letter_becomes_ctrl(void) {
    SDL_Keycode key = SDLK_A;
    SDL_Scancode sc = SDL_SCANCODE_A;
    uint16_t mod = SDL_KMOD_LGUI;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(key == SDLK_A);
    assert(sc == SDL_SCANCODE_A);
    assert(mod == SDL_KMOD_LCTRL);
}

static void test_cmd_shift_keeps_shift(void) {
    SDL_Keycode key = SDLK_Z;
    SDL_Scancode sc = SDL_SCANCODE_Z;
    uint16_t mod = SDL_KMOD_LGUI | SDL_KMOD_LSHIFT;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == (SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT));
}

static void test_cmd_key_itself(void) {
    SDL_Keycode key = SDLK_LGUI;
    SDL_Scancode sc = SDL_SCANCODE_LGUI;
    uint16_t mod = SDL_KMOD_LGUI;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(key == SDLK_LCTRL);
    assert(sc == SDL_SCANCODE_LCTRL);
    assert(mod == SDL_KMOD_LCTRL);

    // release: SDL reports no modifier on the way up
    key = SDLK_RGUI;
    sc = SDL_SCANCODE_RGUI;
    mod = 0;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(key == SDLK_RCTRL);
    assert(sc == SDL_SCANCODE_RCTRL);
    assert(mod == 0);
}

static void test_cmd_arrow_becomes_alt(void) {
    SDL_Keycode key = SDLK_LEFT;
    SDL_Scancode sc = SDL_SCANCODE_LEFT;
    uint16_t mod = SDL_KMOD_LGUI;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(key == SDLK_LEFT);
    assert(mod == SDL_KMOD_LALT);

    key = SDLK_BACKSPACE;
    sc = SDL_SCANCODE_BACKSPACE;
    mod = SDL_KMOD_RGUI | SDL_KMOD_LSHIFT;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == (SDL_KMOD_LALT | SDL_KMOD_LSHIFT));
}

static void test_option_arrow_becomes_ctrl(void) {
    SDL_Keycode key = SDLK_RIGHT;
    SDL_Scancode sc = SDL_SCANCODE_RIGHT;
    uint16_t mod = SDL_KMOD_LALT;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == SDL_KMOD_LCTRL);

    key = SDLK_DELETE;
    sc = SDL_SCANCODE_DELETE;
    mod = SDL_KMOD_RALT;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == SDL_KMOD_LCTRL);
}

static void test_option_letter_stays_alt(void) {
    SDL_Keycode key = SDLK_TAB;
    SDL_Scancode sc = SDL_SCANCODE_TAB;
    uint16_t mod = SDL_KMOD_LALT;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == SDL_KMOD_LALT);
}

static void test_plain_and_ctrl_untouched(void) {
    SDL_Keycode key = SDLK_B;
    SDL_Scancode sc = SDL_SCANCODE_B;
    uint16_t mod = 0;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(key == SDLK_B && sc == SDL_SCANCODE_B && mod == 0);

    mod = SDL_KMOD_LCTRL | SDL_KMOD_CAPS;
    sc_mac_keys_translate(&key, &sc, &mod);
    assert(mod == (SDL_KMOD_LCTRL | SDL_KMOD_CAPS));
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    test_cmd_letter_becomes_ctrl();
    test_cmd_shift_keeps_shift();
    test_cmd_key_itself();
    test_cmd_arrow_becomes_alt();
    test_option_arrow_becomes_ctrl();
    test_option_letter_stays_alt();
    test_plain_and_ctrl_untouched();
    return 0;
}
