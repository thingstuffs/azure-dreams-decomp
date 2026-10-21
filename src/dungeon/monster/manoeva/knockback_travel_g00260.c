/* Knockback travel (G00260).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00260 - CL:dungeon/func_80E3B86C@dungeon/bank_e56c58, CL:dungeon/func_80E3B86C@dungeon/bank_e5d000, CL:dungeon/func_80E3B86C@dungeon/bank_e63000, CL:dungeon/func_80E3B86C@dungeon/bank_e69000, CL:dungeon/func_80E3B86C@dungeon/bank_e6f000, CL:dungeon/func_80E3B86C@dungeon/bank_e75000.
 */
#include "dungeon/monster/manoeva/knockback_travel_g00260.h"

/* Checks the adjacent tile's flags and whether its sampled value is below 0x200. */
s32 check_adjacent_tile_height(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out) {
    u16 tile_flags;
    s16 sample;

    if ((get_offset_map_cell_value_and_flags(tile_x, tile_y, direction, &tile_flags) << 16) == 0) {
        return 0;
    }
    if (!(tile_flags & 0xB700)) {
        sample = sample_terrain_surface_height(
            ((tile_x + dir_step_x[direction]) << 6) + 0x20 & 0xFFE0,
            ((tile_y + dir_step_y[direction]) << 6) + 0x20 & 0xFFE0,
            (s16)(height - 0x20));
        *sample_out = sample;
        if (sample < 0x200) {
            return 1;
        }
    }
    return 0;
}

/* Find a reachable target tile and create an object with the source display and context. */
void create_knockback_travel_object(u8 *owner_data, Position *position_arg, Source *source_arg, Context *context_arg) {
    Vec3s world_offset;
    Vec3s local_offset;
    u16 hit;
    s32 direction;
    s32 trial_dir;
    s32 target_y;
    s32 target_x;
    Object *object;
    SpriteFrameState *display;
    Work *work;
    u8 *special_data;
    s32 offset_x_index;
    s32 owner_byte;
    s32 offset_y_index;
    u32 initial_result;

    target_y = target_x = 0;
    if (context_arg->f60 == ((u8 *)dungeon_actor_ring_anchor)) {
        special_data = *(u8 **)((u8 *)context_arg->f60 + 0x4C);
        if (special_data != 0) {
            if (special_data[1] == 15 && special_data[0] == 8) {
                return;
            }
        }
    }

    if (g_dungeon_status.monster_count >= 32) {
        return;
    }
    if (!find_or_retain_sprite_resource_slot(context_arg->f13, 1) && !find_or_retain_sprite_resource_slot(context_arg->f13, 3)) {
        return;
    }

    direction = (((s16)context_arg->f2A >> 9) + 4) & 7;
    initial_result = (u16)check_adjacent_tile_height(source_arg->x, source_arg->y, position_arg->z, direction, &hit) << 16;
    if (initial_result == 0) {
        for (trial_dir = 0; trial_dir < 8; trial_dir++) {
            if ((s16)check_adjacent_tile_height((s16)(source_arg->x + dir_step_x[direction]),
                                   (s16)(source_arg->y + dir_step_y[direction]),
                                   position_arg->z, (s16)trial_dir, &hit) != 0) {
                target_x = ((u16 *)dir_step_x)[trial_dir] + (source_arg->x + ((u16 *)dir_step_x)[direction]);
                target_y = ((u16 *)dir_step_y)[trial_dir] + (source_arg->y + ((u16 *)dir_step_y)[direction]);
                break;
            }
        }
        if (trial_dir >= 8) {
            return;
        }
    } else {
        target_x = source_arg->x + ((u16 *)dir_step_x)[direction];
        target_y = source_arg->y + ((u16 *)dir_step_y)[direction];
    }

    object = allocate_list_node(0x100, owner_data - 0x20);
    if (object == 0) {
        return;
    }

    display = object->display;
    work = (Work *)((u8 *)object + 0x20);
    object->callback = &D_80174CCC;
    work->source = source_arg;
    work->position = position_arg;

    display->scale_y = 0x1000;
    display->scale_x = 0x1000;
    display->color.word = 0x00808080;
    display->unk_28 = source_arg->f28;
    display->clut = source_arg->f12;

    offset_x_index = ((g_game_work.view.camera_rotation.parts.viewAngle + context_arg->f2A + 0x100) >> 8) & 0xE;
    local_offset.x = D_801766F0[offset_x_index];
    offset_y_index = ((g_game_work.view.camera_rotation.parts.viewAngle + context_arg->f2A + 0x100) >> 8) & 0xE;
    local_offset.y = D_801766F0[offset_y_index + 1];
    local_offset.z = 0;
    project_vector_by_view_angle(&local_offset, &world_offset);

    object->position->x = position_arg->x + world_offset.x;
    object->position->y = position_arg->y + world_offset.y;
    object->position->z = position_arg->z + world_offset.z;
    select_sprite_entry(display, 0x41, 0);
    register_node(object, project_sprite_chain);

    object->field20 = &context_arg->f2A;
    work->f20 = 8;
    work->x = target_x;
    work->y = target_y;
    work->hit = hit;
    work->flags = context_arg->f14 & 0x2007;
    (*(u16 *)((u8 *)work + 0x3A)) = source_arg->f12;
    owner_byte = owner_data[0xAC];
    work->owner_minus20 = (u8 *)context_arg - 0x20;
    work->context = context_arg;
    work->owner_byte = owner_byte;

    g_dungeon_status.activity_counts.parts.pending_action_count++;

    return;
}
