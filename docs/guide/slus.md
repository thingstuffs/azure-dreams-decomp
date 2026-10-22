# SLUS: executable and resident services

[Guide index](README.md) · [Shared engine](engine.md)

`slus` identifies `SLUS_006.14`, the executable, in the
[file catalog](../../config/link_graph/files.000.jsonl). Its source is split
between `src/slus/` and feature folders under `src/engine/`; the
[SLUS row index](../../src/slus/INDEX.md) records both. For example, row
`w_8003D5A4` now lives in engine/scene as `initialize_hardware_and_game_state`.

## Where to read

| Files / folders | Concrete responsibility and starting function |
| --- | --- |
| `src/slus/code.c` | Retained mixed routines: [`initialize_memory_card_services`, `zero_words`, `copy_words_forward`](../../src/slus/code.c) |
| `src/slus/code2.c` | [`set_scene_phase_callback` and `reset_scene_frame_callback_list`](../../src/slus/code2.c) maintain scene callbacks |
| CD command cohort | [`Control_CD`](../../src/slus/w_8003E4FC.c) queues commands; [`service_cd_command_queue`](../../src/slus/w_8003E758.c) advances their state |
| CD-owned storage | [`cd_command_state_owned.c`](../../src/slus/cd_command_state_owned.c) defines queue state and includes cohort members |
| Sound-owned storage / transfers | [`clear_spu_reverb_work_area`](../../src/slus/sound_streaming_transfer.c) transfers zeroed chunks to SPU memory and waits for completion events |
| `src/engine/scene/`, `src/engine/audio/` | Named resident routines such as [`initialize_hardware_and_game_state`](../../src/engine/scene/initialize_hardware_and_game_state.c) and [`init_audio_subsystem`](../../src/engine/audio/init_audio_subsystem.c) |

These are reading entry points, not a claim that every C file is an original
historical TU. The CD storage owner still contains member includes; use the
[layout resolver](../SOURCE_LAYOUT.md) when following an old row name.

## Initialization and one frame

[`initialize_hardware_and_game_state`](../../src/engine/scene/initialize_hardware_and_game_state.c)
initializes video, CD, graphics, audio, controller reply buffers and card
services; it then sets configuration defaults and draw-buffer pointers.
[`render_scene_frame_with_timing`](../../src/engine/scene/render_scene_frame_with_timing.c)
submits display/draw environments and the ordering table, services CD/audio,
runs callbacks, updates buttons, switches buffers, updates objects and performs
the timing synchronization. Read these functions to connect hardware services
to a visible game frame.

The shared state is described by
[`GameWork`, `GameView`, `MapGrid`](../../include/shared/game_work.h): draw-buffer
and controller words, camera/view slots, map pointers and grid dimensions.
[`RuntimeDispatchState`](../../include/shared/runtime_dispatch.h) holds the
mode and dispatch bytes used by scene loading. Unknown fields keep their
neutral names; their presence does not establish an additional game feature.

## How other images are requested

[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
indexes `dispatch_resource_records`, selects a resource type and, when the
nonzero non-movie type changes, packs CD reads from
`scene_resource_group_records`. It drains the queue between chunks. Type 4
sets up the shared movie resource and movie sector/control words instead.
[`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c)
walks an entry's zero-terminated file-command list through `file_load_com`;
[`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c)
walks its function list. The queue implementation is the SLUS service above.

Resource reads can contain code, data or images; trace the selected descriptor
before assigning a particular overlay meaning. The build's load/file views and
additional diagnostic layouts are explained in [BUILD.md](../BUILD.md), and
shared-source placements in [LINK_LISTS.md](../LINK_LISTS.md).
