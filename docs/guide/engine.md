# Engine: objects, scripts and shared services

[Guide index](README.md) · [SLUS](slus.md)

The engine folders group reusable systems by behavior. A useful game-facing
entry is [`update_active_nodes`](../../src/engine/node/update_active_nodes.c):
it runs object callbacks, removes marked objects, integrates motion, updates
the view/map drawing and dispatches registered draw callbacks. Its caller's
frame work is visible in
[`render_scene_frame_with_timing`](../../src/engine/scene/render_scene_frame_with_timing.c).

## Folder map

| Folder group under `src/engine/` | Follow this implementation |
| --- | --- |
| `node/`, `object/`, `entity/` | [`allocate_list_node`](../../src/engine/node/allocate_list_node.c) links an object; [`init_monster_from_stats`](../../src/engine/entity/init_monster_from_stats.c) fills actor stats |
| `scene/`, `resource/`, `cd/`, `runtime/` | [`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c), [`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c), [`drain_cd_command_queue`](../../src/engine/cd/drain_cd_command_queue.c) and [`set_resident_bit`](../../src/engine/runtime/set_resident_bit.c) |
| `script/`, `script/vm/` | [`start_script`](../../src/engine/script/start_script.c), [`call_script`](../../src/engine/script/call_script.c), and [`vm_op_46_call_function_table`](../../src/engine/script/vm/vm_op_call_function_table.c) expose script execution and dispatch |
| `graphics/`, `camera/`, `texture/`, `sprite/`, `effect/` | The drawing path in [`update_active_nodes`](../../src/engine/node/update_active_nodes.c) calls view, map and primitive routines; [`run_image_load_commands`](../../src/engine/graphics/run_image_load_commands.c) handles image decoding/uploads |
| `menu/`, `window/`, `message/`, `text/`, `input/` | [`create_animated_selection_menu`](../../src/engine/menu/create_animated_selection_menu.c) creates an interactive menu; [`draw_glyph_row`](../../src/engine/graphics/draw_glyph_row.c) is a small text-rendering starting point; [`update_controller_buttons_and_triggers`](../../src/engine/scene/update_controller_buttons_and_triggers.c) computes button history |
| `audio/`, `audio/sequence/`, `audio/slots/`, `audio/spu/` | [`init_audio_subsystem`](../../src/engine/audio/init_audio_subsystem.c) connects sequence, slot, volume and SPU initialization |
| `item/`, `town/`, `movie/`, `util/` | Feature helpers and wrappers; for example [`town_movie_exe`](../../src/engine/movie/town_movie_exe.c) requests playback and restores dispatch files |

The table gives routes into the folders, not a separate subsystem binary for
each one. For actual container membership use the
[row resolver](../SOURCE_LAYOUT.md) and [placement records](../LINK_LISTS.md).

## Object and script records

[`ObjectNodeHeader`](../../include/shared/object_node.h) is a 0x20-byte list
header. [`allocate_list_node`](../../src/engine/node/allocate_list_node.c)
takes a free node, clears 0x49 words, links `next`/`pprev`, sets flags and
assigns payload pointers according to those flags.
[`run_active_node_callbacks`](../../src/engine/node/run_active_node_callbacks.c)
passes node+0x20, the +0x08 pointer and the +0x0C pointer to eligible callbacks.
For the actor allocation described in
[`entity.h`](../../include/shared/entity.h), these are distinct actor, position
and sprite records; do not interpret all three as an actor body.

[`ObjectPosition`, `ActorRecord`, `PlayerRecord`](../../include/shared/entity.h)
and [`SpriteFrameState`](../../include/shared/sprite_frame_state.h) describe
those records. [`GameWork`](../../include/shared/game_work.h) carries view,
map and input state. For script state, start at the
[`Rec_D_80082A38` view](../../include/records/Rec_D_80082A38.h) used by
[`call_script`](../../src/engine/script/call_script.c); follow each opcode's
actual operands rather than assuming a common argument layout.

## Resource and overlay loading

[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
chooses the group descriptor and queues chunked reads with `Control_CD`.
[`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c)
walks file commands; [`file_load_com`](../../src/engine/scene/file_load_com.c)
resolves packed addresses, drains the CD queue, then calls
[`run_image_load_commands`](../../src/engine/graphics/run_image_load_commands.c).
That command interpreter decompresses or copies data, uploads VRAM content and
handles address adjustments. Callback lists are invoked separately by
[`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c).
This is the shared route to investigate for town, dungeon and movie transitions;
an image-load command is not by itself proof that a particular monster bank runs.
