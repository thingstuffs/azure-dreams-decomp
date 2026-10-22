# Town: scenes, people, buildings and shops

[Guide index](README.md) · [Engine services](engine.md)

Town behavior is visible in script-facing functions such as
[`select_next_dialogue_line`](../../src/town/scene/dialogue/select_next_dialogue_line.c),
which tests progress flags and state before returning a text pointer, and
[`CheckBuildBuildingLand`](../../src/town/map/check_build_building_land.c),
which checks building assignments and land attributes. These are useful
starting points for connecting town interactions to the data they inspect.

## Folder map

| Folder under `src/town/` | Feature and implementation to follow |
| --- | --- |
| `map/` | Building/map state: [`CheckBuildBuildingLand`](../../src/town/map/check_build_building_land.c) and [`BuildLandBuilding`](../../src/town/map/build_land_building.c), which records selected palettes |
| `scene/` | Scene/script helpers, including `dialogue/` ([`select_next_dialogue_line`](../../src/town/scene/dialogue/select_next_dialogue_line.c)) and `money/` ([`has_money_at_least`](../../src/town/scene/money/has_money_at_least.c)) |
| `person/` | Actor lookup and behavior: [`anyone_now_pos_get`](../../src/town/person/anyone_now_pos_get.c) reads an indexed object's position into script variables |
| `player/` | Input and interaction: [`update_actor_input_and_interaction`](../../src/town/player/input/update_actor_input_and_interaction.c) combines motion/collision work with action dispatch |
| `shop/` | Shop-entry and display helpers: [`refresh_lshop_entry_list`](../../src/town/shop/refresh_lshop_entry_list.c) releases an entry then compacts the list |
| `menu/` | Catalog UI: [`handle_catalog_grid_input`](../../src/town/menu/input/handle_catalog_grid_input.c) handles selection and exit actions |
| `minigame/` | Separate game controllers; [`initialize_mogura_minigame`](../../src/town/minigame/initialize_mogura_minigame.c) initializes state and linked display objects |
| `event/` | Action/object helpers, such as [`resolve_owner_position_and_dispatch`](../../src/town/event/resolve_owner_position_and_dispatch.c) |
| `system/` | Shared town support; [`create_item_menu_child_object`](../../src/town/system/actor_display_resource.c) allocates a child object and attaches display resources |
| `devkit/` | Retained diagnostic paths; [`dev_report_kind_mode_sno`](../../src/town/devkit/dev_report_kind_mode_sno.c) prints kind, mode and scene/sequence values |

The `animation`, `motion`, `object`, `position`, `state` and other feature
subfolders narrow these groups. Use the owning
[`include/town/`](../../include/town/) headers and
[town row index](../../src/town/INDEX.md) to follow an individual callback.
Flat address-named files still exist; resolve their row IDs rather than
guessing a behavior from their address.

## State and a reading route

[`Rec_D_80016000`](../../include/shared/town_root.h), reached through the
`D_80016000` pointer, contains service and state pointers typed as
[`TownServiceTable`](../../include/shared/town_services.h) and
[`TownStateRecord`](../../include/shared/town_state.h). Those headers document
observed fields; many remain unknown. In
[`has_money_at_least`](../../src/town/scene/money/has_money_at_least.c), follow
`root->unk_38->unk_2D5C`; in
[`select_next_dialogue_line`](../../src/town/scene/dialogue/select_next_dialogue_line.c),
compare the tested flags from [`script_symbols.h`](../../include/script_symbols.h)
with [`TownEventState`](../../include/shared/town_event_state.h).

For an actor, read
[`anyone_now_pos_get`](../../src/town/person/anyone_now_pos_get.c) alongside
[`ObjectIndexSlot`](../../include/shared/object_index_slots.h) and the
[object callback mechanism](../../src/engine/node/run_active_node_callbacks.c).
It loads the node's +0x08 position pointer; that is separate from the actor
body, as described by [the shared record types](../../include/shared/entity.h).

## Loading town resources

The shared scene loader
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
queues the selected group read. A town-specific reservation layer lives in
[`dungeon/level/townload.c`](../../src/dungeon/level/townload.c):
`reserve_twch_load` selects entries in `town_resource_queue`, and
`load_reserved_slot_resources` walks 15 slots, calling `file_load_com` for
nonzero entries from `town_resource_descriptors`. Its physical location is
another reason to distinguish source folders from game features.

[`file_load_com`](../../src/engine/scene/file_load_com.c) performs the CD read
and dispatches image-load commands; scene function lists are handled by
[`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c).
Follow a reservation to its descriptor and callback before identifying a
specific loaded scene. No reachability claim is implied for all devkit helpers.
