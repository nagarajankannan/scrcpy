#ifndef SC_MAC_KEYS_H
#define SC_MAC_KEYS_H

#include "common.h"

#include <stdint.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>

/**
 * --mac-keys: make a Mac keyboard behave like an Android keyboard.
 *
 * Android editing shortcuts are Ctrl based (Ctrl+A, Ctrl+Z, Ctrl+C, ...),
 * while a Mac uses Cmd. Android moves by word with Ctrl+arrow and to the line
 * ends with Alt+arrow, while a Mac uses Option+arrow and Cmd+arrow. This
 * rewrites one SDL key event in place, before scrcpy handles shortcuts:
 *
 *   Cmd (key and modifier)       -> Ctrl
 *   Cmd + arrow/Backspace/Delete -> Alt + same key   (line, or whole text)
 *   Option + arrow/Backspace/Del -> Ctrl + same key  (word)
 *
 * Everything else, including Shift and the Mac Ctrl key, passes through.
 */
void
sc_mac_keys_translate(SDL_Keycode *keycode, SDL_Scancode *scancode,
                      uint16_t *mod);

#endif
