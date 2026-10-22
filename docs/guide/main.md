# MAIN: container identity and card server

[Guide index](README.md) · [Frontend screens](frontend.md)

`main` is the registry name for `MAIN/MAIN.BIN`, as recorded by the
[file catalog](../../config/link_graph/files.000.jsonl). It is not synonymous
with `src/main/`: the [MAIN index](../../src/main/INDEX.md) also points to
frontend and engine files. The remaining flat `src/main/` C files concentrate
on card-channel operations and save buffers; for example,
[`card_boot_select_channel_mode`](../../src/main/func_8000D924.c) waits for
both channels and requests information for the selected one.

## Folder map and entry points

| Location | What to read |
| --- | --- |
| `src/main/func_*.c` | Retained address filenames; functions inside have card names. [`card_boot_recheck_selected_channel`](../../src/main/func_8000D984.c) drains software events and requests channel information |
| `src/main/modules/` | [`server_ship.c`](../../src/main/modules/server_ship.c) is an include-based server cohort marked diagnostic; its comment leaves original TU boundaries pending review |
| `src/frontend/card/`, `src/frontend/libcard/`, `src/frontend/settings/` | Menus and settings with MAIN lineage; read the [frontend guide](frontend.md), rather than looking for all of MAIN's behavior in this flat folder |

To understand the operation state machine, start at
[`card_boot_poll_state_two_transition`](../../src/main/func_8000E21C.c): it
checks operation state 2, polls the selected channel and either resets to state
0 with result 5 or advances to state 3. The surrounding prototypes are in
[`include/main.h`](../../include/main.h); the cohort's callback and storage
declarations are in
[`main_server_ship.h`](../../include/modules/main_server_ship.h).

For save-buffer handling, read
[`card_boot_store_save_xor_checksum`](../../src/main/func_8000EEB8.c).
It XORs data words starting at +0x208 and writes the checksum at +0x204. This
function establishes that checksum operation, not the meaning of every field
in the save payload.

## Data to keep beside the code

[`main_server_ship.h`](../../include/modules/main_server_ship.h) declares
`MainCardPair`, `CallbackSet` / `CallbackWork`, `MainCardDirectoryEntry` and
`MainSaveSlot`, plus channel, directory and operation-state globals. Its header
explicitly describes these as runtime/storage views without an enclosing
allocation claim. [`main/data.h`](../../include/main/data.h) collects imported
MAIN data declarations. The shared
[`PadState`](../../include/shared/pad_state.h) has held and pressed words with
an unclassified middle word; retain that distinction when following menu input.

## How this connects to loading

The resident scene loader is
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c):
dispatch records select a resource type, reads are queued with `Control_CD`,
and `runtime_dispatch_state.field_4` receives the selected group's entry word.
Additional file lists go through
[`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c)
and callbacks through
[`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c).
Those implementations establish the loading mechanism; the card filenames do
not establish a complete boot sequence or the meaning of every dispatch ID.
For the MAIN load/file output and recipe checks, see [BUILD.md](../BUILD.md).
