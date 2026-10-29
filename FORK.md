# Fork notes

This is `nagarajankannan/scrcpy`, branch `trackpad`, a fork of
[Genymobile/scrcpy](https://github.com/Genymobile/scrcpy) based on `v5.0.1`.
It is used as a submodule of
[nagarajankannan/boox-utils](https://github.com/nagarajankannan/boox-utils),
which holds the build script, the launcher and the full documentation in
`docs/scrcpy-fork.md`. Everything not listed here is upstream scrcpy.

## Added options

`--trackpad`. Two fingers on a macOS trackpad become two touch pointers on the
device, anchored at the mouse cursor, so pinch, rotate and two-finger slides
work as on the device itself. SDL delivers trackpad touches only when the
hint `SDL_HINT_MOUSE_TOUCH_EVENTS` is set, which this option turns on. Only
available with `--mouse=sdk`. Code: `app/src/input_manager.c`, functions
prefixed `trackpad_` and `sc_input_manager_process_trackpad`; pointer ids
`SC_POINTER_ID_TRACKPAD_FINGER_A` and `_B` in `app/src/control_msg.h`; the
hint in `app/src/util/sdl_hints.c`.

`--mac-keys`. A Mac keyboard behaves like an Android keyboard. Cmd is sent
as Ctrl, so Cmd+A, Cmd+Z, Cmd+C, Cmd+V and Cmd+X become the Android
shortcuts. Cmd+arrow is sent as Alt+arrow and Option+arrow as Ctrl+arrow,
which is how Android moves to the line ends and by word. The same swap
applies to Backspace and Delete. Cmd+V keeps scrcpy's clipboard
synchronization. Unless `--shortcut-mod` is given, scrcpy's own shortcuts
move to Right Option so that Cmd and Left Option reach the device. Code:
`app/src/mac_keys.c` (a pure translation of one SDL key event), called at the
top of `sc_input_manager_process_key` in `app/src/input_manager.c`; unit
test in `app/tests/test_mac_keys.c`.

## Touched files

`app/src/cli.c`, `app/src/options.h`, `app/src/options.c`, `app/src/scrcpy.c`,
`app/src/screen.h`, `app/src/screen.c`, `app/src/input_manager.h`,
`app/src/input_manager.c`, `app/src/control_msg.h`, `app/src/util/sdl_hints.c`,
`app/src/util/sdl_hints.h`, `app/src/usb/scrcpy_otg.c`, `app/src/mac_keys.h`,
`app/src/mac_keys.c`, `app/tests/test_mac_keys.c`, `app/meson.build`.

## Rebasing on upstream

```
git remote add upstream https://github.com/Genymobile/scrcpy.git   # once
git fetch upstream
git rebase upstream/master
```

The server is unchanged, so the prebuilt server of the matching upstream
release is used. Run the tests with a debug build:
`meson setup build-debug --buildtype=debug -Dcompile_server=false
-Dprebuilt_server=<path>` then `meson test -C build-debug`.
