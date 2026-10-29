#include "mac_keys.h"

#include <stdbool.h>

static bool
is_navigation_key(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_BACKSPACE:
        case SDLK_DELETE:
            return true;
        default:
            return false;
    }
}

void
sc_mac_keys_translate(SDL_Keycode *keycode, SDL_Scancode *scancode,
                      uint16_t *mod) {
    // The Cmd key itself is reported as a key press: send it as Ctrl
    switch (*keycode) {
        case SDLK_LGUI:
            *keycode = SDLK_LCTRL;
            break;
        case SDLK_RGUI:
            *keycode = SDLK_RCTRL;
            break;
        default:
            break;
    }
    switch (*scancode) {
        case SDL_SCANCODE_LGUI:
            *scancode = SDL_SCANCODE_LCTRL;
            break;
        case SDL_SCANCODE_RGUI:
            *scancode = SDL_SCANCODE_RCTRL;
            break;
        default:
            break;
    }

    uint16_t m = *mod;
    bool cmd = m & SDL_KMOD_GUI;
    bool option = m & SDL_KMOD_ALT;
    m &= ~(SDL_KMOD_GUI | SDL_KMOD_ALT);
    if (is_navigation_key(*keycode)) {
        // Android: Alt+arrow = line start/end, Ctrl+arrow = word
        if (cmd) {
            m |= SDL_KMOD_LALT;
        }
        if (option) {
            m |= SDL_KMOD_LCTRL;
        }
    } else {
        if (cmd) {
            m |= SDL_KMOD_LCTRL;
        }
        if (option) {
            m |= SDL_KMOD_LALT;
        }
    }
    *mod = m;
}
