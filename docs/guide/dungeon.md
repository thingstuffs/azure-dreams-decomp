# Dungeon: floors, actors and monster actions

[Guide index](README.md) · [Engine objects](engine.md)

Start with [`initialize_dungeon_floor_state`](../../src/dungeon/level/setup.c):
it initializes records, chooses or restores the floor, prepares resources and
sets monster data. Then compare
[`advance_actor_action_controller`](../../src/dungeon/actor/advance_actor_action_controller.c),
whose state switch advances actor actions and directional animation. Together
they connect floor setup to the per-actor update path without assuming that a
filename is itself a runtime entry point.

## Folder map

| Folder under `src/dungeon/` | Feature and concrete implementation |
| --- | --- |
| `level/` | [`initialize_floor_generation_state`, `initialize_dungeon_floor_state`](../../src/dungeon/level/setup.c); [`clear_generation_cell_grid`, `mask_generation_cell_rect`, `load_floor_spawn_tables`](../../src/dungeon/level/generate.c) |
| `actor/` | Shared actor actions and status: [`advance_actor_action_controller`](../../src/dungeon/actor/advance_actor_action_controller.c), [`spend_actor_mp`](../../src/dungeon/actor/spend_actor_mp.c) |
| `player/` | Player/familiar commands: [`begin_familiar_summoning`](../../src/dungeon/player/begin_familiar_summoning.c) sets action state and searches for a valid nearby position |
| `monster/<name>/` | Monster-specific action callbacks; [`start_kewne_attack_action`](../../src/dungeon/monster/kewne/start_kewne_attack_action.c) selects animation and prepares a directional attack |
| `item/` | Item-action dispatch, e.g. [`apply_return_magic_item`](../../src/dungeon/item/apply_return_magic_item.c), whose branches distinguish target kinds and actor state |
| `effect/` | Visual processing, e.g. [`transform_and_queue_mesh_primitives`](../../src/dungeon/effect/mesh/transform_and_queue_mesh_primitives.c) |
| `menu/` | Dungeon menus; start by following [`process_dungeon_menu_selection`](../../src/dungeon/player/process_dungeon_menu_selection.c) into the selected handlers |
| `system/`, `modules/` | Supporting routines and retained cohorts; [`submit_control_and_reset_status`](../../src/dungeon/system/submit_control_and_reset_status.c) is a small CD-control example |

The `motion`, `position`, `object`, `state`, `mesh`, `particle` and other
subfolders separate those kinds of work. Use the
[dungeon row index](../../src/dungeon/INDEX.md) for row membership and the
[source resolver](../SOURCE_LAYOUT.md) for merged files and shared homes.
Monster variant labels are provisional where the
[layout decisions](../evidence/r97_decisions.md) say so; a directory name alone
does not establish a species-to-bank mapping.

## Records worth opening first

[`GameWork.map` / `MapGrid`](../../include/shared/game_work.h) describe map
cell pointers, dimension shifts, masks and spans.
[`mask_generation_cell_rect`](../../src/dungeon/level/generate.c) shows indexing
as `x + (y << shiftX)`; the generation grid uses six-byte cells.
[`DungeonGlobalStatus`](../../include/shared/dungeon_status.h) holds action and
movement counts, active actor, monster spawn table and turn counter.

The actor body is [`ActorRecord`](../../include/shared/entity.h); position and
sprite records are separate [`ObjectPosition`](../../include/shared/entity.h)
and [`SpriteFrameState`](../../include/shared/sprite_frame_state.h).
[`advance_actor_action_controller`](../../src/dungeon/actor/advance_actor_action_controller.c)
accepts both sprite and actor pointers and uses view angle plus actor facing
for animation selection. The player extends the actor prefix as `PlayerRecord`.
Actor MP is stored at +0x24/+0x25 and capped by +0x66; compare
[`spend_actor_mp`](../../src/dungeon/actor/spend_actor_mp.c) with
[`feed_actor_restore_mp`](../../src/dungeon/actor/feed_actor_restore_mp.c).
Legacy `EntityRec` users remain where record-kind recovery is held; see
[decision 73](../evidence/r97_decisions.md).

## Floor and resource loading

[`reset_dungeon_runtime_state`](../../src/dungeon/level/setup.c) conditionally
loads a set of file descriptors and a sprite bundle.
`initialize_dungeon_floor_state` can pack a floor-specific CD read, submit it
through `Control_CD` and drain the queue.
[`load_floor_spawn_tables`](../../src/dungeon/level/generate.c) reads a resource
into `D_8014A000`, copies two 32-byte table blocks and records a track variant.
These are distinct resource operations; they are not evidence that every bank
contains a whole floor.

The outer scene read mechanism is
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c);
file commands go through [`file_load_com`](../../src/engine/scene/file_load_com.c).
[BUILD.md](../BUILD.md) distinguishes dungeon bank/load images from extra
recipe/placement checks. Matching a diagnostic layout proves its bytes, not
when that layout is active during play.
