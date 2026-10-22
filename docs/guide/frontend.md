# Frontend: card screens and settings

[Guide index](README.md) · [MAIN card services](main.md)

The frontend source builds visible menus on top of the card and object
services. For example,
[`card_boot_create_slot_selection_menu`](../../src/frontend/libcard/card_boot_create_slot_selection_menu.c)
creates a scene object, initializes its request, refreshes card-directory
information, creates child panels and installs an update callback.
[`initialize_settings_screen`](../../src/frontend/settings/initialize_settings_screen.c)
builds settings labels, panels and sliders and installs input/drawing callbacks.

## Folder map

| Folder under `src/frontend/` | Concrete example |
| --- | --- |
| `card/` | Card UI and retained devkit paths: [`card_dev_create_load_screen`](../../src/frontend/card/card_dev_create_load_screen.c) allocates a screen object, installs its callback and creates background/info components |
| `card/load/` | Load-screen behavior: [`handle_menu_selection_input`](../../src/frontend/card/load/handle_menu_selection_input.c) processes a menu selection |
| `card/save/` | Save-screen behavior: [`card_devkit_build_save_slot_windows`](../../src/frontend/card/save/card_devkit_build_save_slot_windows.c) constructs slot windows |
| `card/menu/`, `card/message/`, `card/service/` | Further UI and operation helpers; use their [folder headers](../../include/frontend/card/) and follow calls from the selected screen |
| `libcard/` and its `message/`, `resource/`, `state/` folders | Another card-menu cohort: [`card_boot_create_slot_selection_menu`](../../src/frontend/libcard/card_boot_create_slot_selection_menu.c) and [`card_boot_handle_overwrite_answer`](../../src/frontend/libcard/card_boot_handle_overwrite_answer.c) |
| `settings/` | [`initialize_settings_screen`](../../src/frontend/settings/initialize_settings_screen.c) and [`handle_settings_menu_input`](../../src/frontend/settings/handle_settings_menu_input.c) |

`card` and `libcard` are source-folder names, not a claim that one is wholly
Sony library code. The implementations above construct game UI and use game
state; SDK stand-in declarations live separately in
[`include/sdk/`](../../include/sdk/).

## Follow one screen

[`initialize_settings_screen`](../../src/frontend/settings/initialize_settings_screen.c)
restores three volume-slider levels, sets up the palette and allocates the
settings object. It installs `handle_settings_menu_input` at the object
callback slot and registers `build_settings_sprite_tiles` for drawing.
[`handle_settings_menu_input`](../../src/frontend/settings/handle_settings_menu_input.c)
has a state switch: it changes selection/slider values, updates sound-volume
scales, commits display settings and advances the fade/exit sequence.

The input function's local `Menu` and `Gfx` types are useful views of settings
state; [`GameWork`](../../include/shared/game_work.h) provides button words.
For card storage use the views in
[`main_server_ship.h`](../../include/modules/main_server_ship.h), not the
settings `Menu` layout. Object headers and payloads are explained by
[`allocate_list_node`](../../src/engine/node/allocate_list_node.c) and
[`ObjectNodeHeader`](../../include/shared/object_node.h).

## Loading and callbacks

The [MAIN index](../../src/main/INDEX.md) maps these frontend files to rows in
the MAIN container. Scene resources are selected by the resident
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
and [`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c),
then dispatch callbacks are run by
[`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c).
Once created, objects participate in the shared
[`run_active_node_callbacks`](../../src/engine/node/run_active_node_callbacks.c)
loop. Do not assume all retained devkit screens are reachable in ordinary play
merely because their source is present.
