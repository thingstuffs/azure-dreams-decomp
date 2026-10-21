/* Action target selection (G00359). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800C4A80, CL:dungeon/func_800C4CE4, CL:dungeon/func_800C5028, CL:dungeon/func_800C51DC, CL:dungeon/func_800C5334. */
#include "dungeon/actor/action_target_selection_g00359.h"

/* Checks whether a directional step is in bounds and clear of obstacles. */
s32 get_adjacent_tile_for_action(u32 action_flags, EntityRec *position, S_800CA1E0_2 *object, u16 height_offset) {
    u16 tile_flags;
    s16 direction;
    u16 target_x;
    u16 target_y;
    u32 world_x;
    u32 world_y;
    MapGrid *map;
    u16 height;
    s16 room;

    direction = (action_flags >> 9) & 7;
    target_x = position->tileX + (u16)dir_step_x[direction];
    map = &g_game_work.map;
    if (target_x == 0 || ((1 << map->shiftX) - 1) < target_x) {
        return -1;
    }
    target_y = position->tileY + (u16)dir_step_y[direction];
    if (target_y == 0 || ((1 << map->shiftY) - 1) < target_y) {
        return -1;
    }
    world_x = position->tileX << 6;
    world_y = position->tileY << 6;
    target_x = world_x + 0x20;
    height = object->unk_88;
    target_y = world_y + 0x20;
    if ((check_diagonal_side_height((u16)direction, target_x >> 6, target_y >> 6, (s16)(height - height_offset)) << 16) == 0) {
        return 0;
    }
    target_x = D_800DCEAC[direction] + target_x;
    target_y = D_800DCEBC[direction] + target_y;
    get_offset_map_cell_value_and_flags(position->tileX, position->tileY, direction, &tile_flags);
    if (tile_flags & 0x8002) {
        return 0;
    }
    if ((s8)position->unk_26 < 0) {
        room = find_active_rect_containing_point((position->tileX + (u16)dir_step_x[direction]) & 0xFFFF, (position->tileY + (u16)dir_step_y[direction]) & 0xFFFF);
        if (room >= 0 && (D_800E2970[room].flags & 2) && !(object->unk_1C & 0x2000)) {
            return 0;
        }
    }
    if ((s16)sample_terrain_surface_height(target_x, target_y, (s16)(height - height_offset)) >= 0x201) {
        return -1;
    }
    return 1;
}

/* Find a movement direction, record the tile, and update the actor's position and height. */
void update_actor_targeting_for_tile(void *motion, s32 unused, S_800CA444_0 *tile, void *actor) {
    s16 next_heading;
    s16 height;
    s16 scan_result;
    s32 heading;
    s32 heading_offset;
    s16 *heading_offsets;
    TileObject *map_state;
    s32 direction_index;
    s8 tile_type;

    if (g_dungeon_status.flags & 0x4000) {
        update_actor_status_and_food(actor);
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        return;
    }
    update_actor_proximity_flag(tile, actor, 3, 6, motion + 0x9C);
    tile_type = tile->unk_26;
    if (tile_type >= 0 && (D_800E2970[tile_type].flags & 2)) {
        rebuild_monster_reachable_tiles(tile, ((S_800CA444_2 *)motion)->unk_9C, actor, motion + 0x98);
    } else if (!(((S_800CA444_1 *)actor)->unk_46 & 0x8000)) {
        rebuild_monster_reachable_tiles(tile, ((S_800CA444_2 *)motion)->unk_9C, actor, motion + 0x98);
    }
    scan_result = 0;
    heading_offsets = D_8006CD00;
    map_state = &D_80082E80;
    for (; scan_result < 8; scan_result++) {
        heading = ((S_800CA444_1 *)actor)->unk_2A;
        if (((S_800CA444_2 *)motion)->unk_98 & 2) {
            heading_offset = heading_offsets[scan_result];
            next_heading = heading - heading_offset;
        } else {
            heading_offset = heading_offsets[scan_result];
            next_heading = heading + heading_offset;
        }
        if ((get_adjacent_tile_for_action(next_heading, tile, actor, 0x20) << 0x10) > 0) {
            ((S_800CA444_1 *)actor)->unk_2A = next_heading;
            ((ActorStatusBytesView *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_74 = tile->unk_24.at00.v;
            ((ActorStatusBytesView *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_7C = tile->unk_24.at01.v;
            ((S_800CA444_1 *)actor)->unk_71++;
            direction_index = (((u16) ((S_800CA444_1 *)actor)->unk_2A) >> 9) & 7;
            tile->unk_24.at00.v += dir_step_x[direction_index];
            tile->unk_24.at01.v += dir_step_y[direction_index];
            break;
        }
        if (scan_result == 0 && *(u16 *)(&map_state->tile_position.parts.tile_x) != tile->unk_24.at00u.v) {
            if ((check_entity_relation(actor, ((S_800CA444_4 *)(((int)D_800814A8)))->unk_58 + 0x20) << 0x10) != 0) {
                return;
            }
        }
    }

    if (scan_result >= 8) {
        ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
        ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
        update_actor_status_and_food(actor);
        return;
    }
    ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
    ((S_800CA444_2 *)motion)->unk_9C = (s8) (u8) tile->unk_26;
    ((S_800CA444_1 *)actor)->unk_6D.u = (u8) (((S_800CA444_1 *)actor)->unk_6D.u - 1);
    g_dungeon_status.activity_counts.parts.pending_movement_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_movement_count) + 1);
    if (((S_800CA444_1 *)actor)->unk_6D.s == 0) {
        ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
        return;
    }
    scan_result = (s16)sample_terrain_surface_height((tile->unk_24.at00.v << 6) | 0x20, (tile->unk_24.at01.v << 6) | 0x20,
        (s16) (((S_800CA444_1 *)actor)->unk_88 - 0x20));
    height = scan_result;
    if (height < 0x200) {
        ((S_800CA444_1 *)actor)->unk_88 = (u16) scan_result;
    }
}

/* Attempt an action toward the target and decrement the actor counter on success. */
s32 select_target_tile_for_actor_action(void *object_ptr, void *action_context, void *target_ptr, void *actor_ptr)
{
    s32 target_direction;
    s32 clear_action_flag;
    u8 *object;
    u8 *actor;
    void *context;
    void *target;
    u16 global_flags;

    object = object_ptr;
    actor = actor_ptr;
    actor[0x71] &= 0x7F;
    context = action_context;
    if (!(g_dungeon_status.flags & 0x2000)) {
        target = target_ptr;

        ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
        target_direction = find_eligible_entry_at_coordinates(actor, ((MovingTile *)target)->unk_24, ((MovingTile *)target)->unk_25);
        clear_action_flag = ~0x2000;
        ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
        ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
        global_flags = g_dungeon_status.flags;
        if (!(global_flags & 0x2000)) {
            goto check_flag_8;
        }
    }
fail:
    return -1;
check_flag_8:
    if (global_flags & 8) {
        goto fail;
    }

    if ((u32)((-get_actor_height_difference(target_direction, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        goto fail;
    }

    apply_camera_offset_and_select_target(actor - 0x20, context, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        goto fail;
    }

    {
        void *action_actor;
        void *action_target;
        s32 actor_param;
        s32 action_mode;

        action_actor = actor;
        action_target = target;
        object[0x9B] = 0;
        ((S_800CA788_3 *)object)->unk_8C = 0;
        object[0x9A] = 0x11;
        actor_param = ((S_800CA788_1 *)actor)->unk_2A;
        actor[0x84] = 0x80;
        action_mode = 0;
        actor[0x85] = 0;
        ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
        prepare_directional_attack(action_actor, action_target, actor_param, action_mode, 0);
    }
    ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
    ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
    actor[0x6D]--;
    return 1;
}

/* Selects a target and updates the object's state before dispatching its action. */
s32 choose_best_eligible_entry_for_actor(void *actor_arg, s32 action_arg, MovingTile *origin) {
    void *actor;
    s32 clear_flag_mask;
    MovingTile *target;
    s32 found_entry;
    void *target_entry;

    actor = actor_arg;
    ((S_800CA93C_0 *)actor)->unk_14 |= 0x2000;
    ((S_800CA93C_0 *)actor)->unk_1C |= 0x2000;
    ((S_800CA93C_0 *)actor)->unk_60 = choose_best_eligible_entry(origin, actor, 4);

    clear_flag_mask = -0x2001;
    ((S_800CA93C_0 *)actor)->unk_14 &= clear_flag_mask;
    target_entry = ((S_800CA93C_0 *)actor)->unk_60;
    ((S_800CA93C_0 *)actor)->unk_1C &= clear_flag_mask;
    if (target_entry != 0) {
        target = ((SpriteLinkPrefixView *)target_entry)[-1].unk_00;
        ((S_800CA93C_0 *)actor)->unk_14 |= 0x2000;
        ((S_800CA93C_0 *)actor)->unk_1C |= 0x2000;
        found_entry = find_eligible_entry_at_coordinates(
            actor,
            origin->unk_24,
            origin->unk_25);
        ((S_800CA93C_0 *)actor)->unk_14 &= clear_flag_mask;
        ((S_800CA93C_0 *)actor)->unk_1C &= clear_flag_mask;
        if (found_entry == (s32)((S_800CA93C_0 *)actor)->unk_60) {
            select_target_tile_for_actor_action(actor, action_arg, origin, actor);
            return 0;
        }
        ((S_800CA93C_0 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
            origin->unk_24,
            origin->unk_25,
            target->unk_24,
            target->unk_25,
            (u8 *)actor + 0x98);
        ((S_800CA93C_0 *)actor)->unk_46 |= 0x8000;
    }

    update_actor_targeting_for_tile(actor_arg, action_arg, origin, actor);
    return 0;
}
