#include "modules/dungeon_ovl_1840800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"

extern int abs(int);





/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_1840800_entry)(void *, TrailMotion *, void *) = func_80024020;

/* Moves an attack toward its target, spawns trailing effects, and applies the hit. */
void func_80024020(void *state, TrailMotion *motion, void *source_data) {
    TrailEffectState *state_obj;
    TrailObject *owner;
    TrailSprite *source;
    TrailActor *actor;
    u32 header_raw;
    TrailSprite *target_data;
    TrailParticleData *effect_data;
    TrailSpawnedObject *effect;
    TrailSprite *actor_data;
    s32 step_x;
    s32 step_y;
    s32 offset_x;
    s32 offset_y;
    s32 distance_or_script;
    s32 abs_y;
    s32 dir_offset;
    s32 coord_x;
    s32 velocity_x;
    s32 velocity_y;
    s32 phase;
    s32 start_y;
    s32 end_x;
    s32 coord_y;
    u16 duration;
    state_obj = state;
    source = source_data;
    actor = state_obj->unk_00;
    owner = (void *) ((u8 *) actor - 0x20);
    header_raw = actor->unk_2A;
    coord_x = header_raw >> 8;
    dir_offset = coord_x & 0xE;
    actor_data = ((TrailObject *) ((u8 *) actor - 0x20))->unk_0C;
    step_x = *(s16 *)((u8 *)dir_step_x + dir_offset);
    step_y = *(s16 *)((u8 *)dir_step_y + dir_offset);
    if (state_obj->unk_0A == 1) {
        motion->unk_00.unk_00 = (s32) (motion->unk_00.unk_00 + motion->unk_0C);
        motion->unk_04.unk_04 = (s32) (motion->unk_04.unk_04 + motion->unk_10);
        coord_x = (s16)sample_terrain_surface_height(motion->unk_00.unk_02.unk_02, motion->unk_04.unk_06.unk_06,
            (s16) (((TrailHeightView *) owner->unk_08)->unk_0A - 0x30));
        if (coord_x < 0x200) {
            motion->unk_0A = coord_x;
        }
    }
    phase = state_obj->unk_0A;
    state_obj->unk_50 = (u16) (state_obj->unk_50 - 1);
    switch (phase) {
    case 0:
    if (!(*state_obj->unk_04 & 0x80)) {
        return;
    }
    {
        TrailSprite *tile_data;
        s32 search_mode;
        start_y = (s16)get_definition_entry_byte_13(3);
        search_mode = start_y << 0x10;
        tile_data = actor_data;
        end_x = tile_data->unk_24;
        header_raw = (u32)scan_monster_along_heading(actor, end_x, tile_data->unk_25, (s16) actor->unk_2A, search_mode >> 0x10);
    }
    actor->unk_60 = (TrailActor *)header_raw;
    if (((TrailActor *)header_raw) == 0) {
        distance_or_script = 0;
        offset_y = 0;
        offset_x = 0;
        do {
            {
                TrailSprite *tile_data = actor_data;
                s32 tile_left;
                s32 tile_left_2;
                s32 tile_top;
                tile_left_2 = (tile_data->unk_24 + offset_x) << 6;
                coord_x = tile_left_2 + 0x20;
                tile_top = (tile_data->unk_25 + offset_y) << 6;
                coord_y = tile_top + 0x20;
            }
            effect = (TrailSpawnedObject *)(u32)(u16)coord_x;
            if ((check_enabled_neighbor_height((u32)effect, (u16)coord_y, (s16)sample_terrain_surface_height((u32)effect, (u16)coord_y, -0x400),
                (s16)actor->unk_2A, actor->unk_60) << 0x10) != 0) {
                break;
            }
            distance_or_script += 1;
            offset_y += step_y;
            offset_x += step_x;
        } while (distance_or_script < 2);
        {
            TrailSprite *tile_data = actor_data;
            actor->unk_72 = (u8) (tile_data->unk_24 + (step_x * distance_or_script));
            actor->unk_73 = (u8) (tile_data->unk_25 + (step_y * distance_or_script));
        }
    } else {
        target_data = ((TrailObject *) ((u8 *) ((TrailActor *)header_raw) - 0x20))->unk_0C;
        actor->unk_72 = (u8) target_data->unk_24;
        actor->unk_73 = (u8) target_data->unk_25;
        if (target_data->unk_14 & 0x8000) {
            if (source->unk_14 & 0x8000) {
                goto start_hit;
            }
        }
    }
    {
        TrailSprite *tile_data;

        tile_data = actor_data;
        end_x = (s8)actor->unk_72;
        abs_y = (s8)actor->unk_73;
        phase = tile_data->unk_24;
        start_y = tile_data->unk_25;
        coord_x = end_x - phase;
        coord_y = abs_y - start_y;
    }
    distance_or_script = abs(coord_x);
    abs_y = coord_y;
    abs_y = abs(abs_y);
    if (distance_or_script < abs_y) {
        distance_or_script = abs_y;
    }
    state_obj->unk_50 = (u16) (distance_or_script * 0xC);
    motion->unk_00.unk_00 = (s32) (((actor_data->unk_24 << 6) + 0x20) << 0x10);
    motion->unk_04.unk_04 = (s32) (((actor_data->unk_25 << 6) + 0x20) << 0x10);
    motion->unk_0C = (s32) ((step_x << 0x16) / 12);
    motion->unk_10 = (s32) ((step_y << 0x16) / 12);
    play_sound_if_enabled(0x300);
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;

    case 1:
    case 2:
    motion->unk_14 = (s32) (motion->unk_14 + 0x100);
    coord_y = 0;
    if (actor->unk_60 == 0) {
        coord_y = -1;
    }
    coord_x = 2;
    distance_or_script = (s32)&update_flickering_effect_vertices;
next_effect:
    effect = allocate_list_node(0x201, ((s32 *)&D_80083498.next));
    if (effect != 0) {
        effect->unk_10 = distance_or_script;
        register_node(effect, func_80024A1C);
        duration = state_obj->unk_50;
        effect_data = (TrailParticleData *) ((u8 *) effect + 0x20);
        effect_data->unk_54 = coord_y;
        effect_data->unk_52 = duration;
        effect_data->unk_4C = (s16) (func_80069EF8() & 0xFFF);
        effect_data->unk_4E = (u16) motion->unk_14;
        effect_data->unk_04 = (s32) motion->unk_00.unk_00;
        effect_data->unk_08 = (s32) motion->unk_04.unk_04;
        effect_data->unk_0C = 0;
        velocity_x = motion->unk_0C;
        effect_data->unk_1C = velocity_x;
        effect_data->unk_10 = velocity_x;
        velocity_y = motion->unk_10;
        effect_data->unk_24 = 0xFFFD0000;
        effect_data->unk_18 = 0xFFFD0000;
        effect_data->unk_20 = velocity_y;
        effect_data->unk_14 = velocity_y;
        effect_data->unk_50 = (u16) motion->unk_0A;
        effect->unk_20 = state_obj;
        effect_data->unk_56 = (s16) ((u16) state_obj->unk_0A - 1);
    }
    coord_x -= 1;
    if (coord_x >= 0) {
        goto next_effect;
    }
    if ((s16) state_obj->unk_50 > 0) {
        return;
    }
    state_obj->unk_50 = 5U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    if (actor->unk_60 != 0) {
        return;
    }
start_hit:
    state_obj->unk_0A = 3;
    return;
    case 3:
    if (actor->unk_60 != 0) {
        apply_attack_power_and_element_effects(actor->unk_60, 0x10, state_obj->unk_09, 4, (s32) (s16) actor->unk_2A, actor, 2);
    }
    state_obj->unk_50 = 0x10U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
    case 4:
    if ((s16) state_obj->unk_50 > 0) {
        return;
    }
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
    case 5:
    if (state_obj->unk_52 & 0x8000) {
        state_obj->unk_52 = (s16) ((u16) state_obj->unk_52 & 0x7FFF);
        return;
    }
    g_dungeon_status.active_actor = 0;
    *(u16 *)((u8 *)state_obj - 2) = (u16) (*(u16 *)((u8 *)state_obj - 2) | 0x8000);
    object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    return;
    }
}



/* Update a dungeon effect's motion, flickering vertices, and fade state. */
void update_flickering_effect_vertices(DungeonObj *obj)
{
    s32 height_or_index;
    s32 old_timer;
    s32 vertex_extent;
    s32 size_jitter;
    s32 vertex_size;
    s32 size_random;
    s32 query_height;
    s32 z_offset;
    s32 packet_height;
    u8 *vertex_cursor;
    LocalPacket packet;

    obj->parent->timer |= 0x8000;
    old_timer = obj->timer--;
    if ((s16)old_timer < 0) {
        obj->state++;
        switch (obj->state) {
        case 1:
            obj->timer = 5;
            if (obj->aux >= 0) {
                break;
            }
            obj->state++;
                                    /* fall through */
        case 2:
            obj->timer = 12;
            obj->dx *= 2;
            obj->dy *= 2;
            break;
        }
    }

    if (obj->state == 1 && *(s16 *)((u8 *)obj + 0x52) < 5) {
        obj->aux = 1;
        obj->red += (0xFF - obj->red) >> 2;
        obj->green += (0x80 - obj->green) >> 2;
    } else if (obj->state < 2) {
        height_or_index = (-*(s16 *)((u8 *)obj + 0x0E) >> 2) + 15;
        if (height_or_index < 16) {
            height_or_index = 16;
        }
        obj->red = (((func_80069EF8() & 15) + 0xBE) << 4) / height_or_index;
        obj->green = (((func_80069EF8() & 15) + 0x91) << 4) / height_or_index;
        obj->blue = (((func_80069EF8() & 15) + 10) << 4) / height_or_index;
    }

    obj->angle = (obj->angle + ((func_80069EF8() & 0xFF)
                  - (*(u16 *)((u8 *)obj + 0x0E) << 2))) & 0xFFF;

    if (obj->z < (s32)0xFFD00000 || obj->state == 3) {
        *((u16 *)obj - 1) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }

    if (obj->state == 0) {
        obj->x += obj->dx;
        obj->y += obj->dy;
    }

    query_height = obj->height;
    query_height -= 0x30;
    query_height = (s16)query_height;
    height_or_index = (s16)sample_terrain_surface_height(*(u16 *)((u8 *)obj + 6),
                           *(u16 *)((u8 *)obj + 0x0A), query_height);
    if (height_or_index < 0x200) {
        obj->height = height_or_index;
    }

    if (obj->state < 2) {
        obj->dz += 0x1700;
        obj->z += obj->dz;

        height_or_index = -*(s16 *)((u8 *)obj + 0x0E);
        size_random = func_80069EF8();
        vertex_size = (height_or_index >> 1) + ((height_or_index >> 3) * (height_or_index >> 4));
        height_or_index = 3;
        size_random &= 7;
        size_random += 8;
        vertex_extent = vertex_size + size_random;
        obj->vy1 = vertex_extent;
        obj->vx0 = vertex_extent;

        size_random = func_80069EF8();
        vertex_cursor = (u8 *)obj + 0x18;
        size_jitter = (size_random & 7) + 8;
        vertex_size += size_jitter;
        vertex_size = -vertex_size;
        obj->vy3 = vertex_size;
        obj->vx2 = vertex_size;
        obj->vx3 = 0;
        obj->vy2 = 0;
        obj->vx1 = 0;
        obj->vy0 = 0;
        obj->angle2 += 0x100;

        do {
            *(u16 *)(vertex_cursor + 0x2C) = func_80069EF8() & 15;
            vertex_cursor -= 8;
        } while (--height_or_index >= 0);

        packet.p0 = &obj->vx0;
        packet.p4 = &obj->vx0;
        packet.hA = 0;
        packet.h8 = 0;
        packet.angle = obj->angle;
        packet.x = *(u16 *)((u8 *)obj + 6)
        + (func_80064584(*(s16 *)((u8 *)obj + 0x4E)
            + (*(s16 *)((u8 *)obj + 0x0E) << 4)) >> 8);
        packet.y = *(u16 *)((u8 *)obj + 0x0A)
        + (func_800644B8(*(s16 *)((u8 *)obj + 0x4E)
            + (*(s16 *)((u8 *)obj + 0x0E) << 4)) >> 8);
        {
            LocalPacket *packet_ptr = &packet;
            z_offset = *(u16 *)((u8 *)obj + 0x0E);
            packet_height = obj->height + (z_offset << 1);
            packet.height = packet_height;
            packet.type = 4;
            packet.pad1A = 0;
            transform_rotated_vertices(packet_ptr);
        }
        return;
    }

    obj->red -= obj->red >> 2;
    obj->green -= obj->green >> 2;
    obj->blue -= obj->blue >> 2;
    if (*(s16 *)((u8 *)obj + 0x52) < 10) {
        {
            DungeonFinalView *vertex_view = (DungeonFinalView *)obj;
            height_or_index = 3;
            do {
                vertex_view->block.v[height_or_index].x += *(u16 *)((u8 *)obj + 0x12);
                vertex_view->block.v[height_or_index].y += *(u16 *)((u8 *)obj + 0x16);
            } while (--height_or_index >= 0);
        }
    }
}




/* Draw four jittered triangles per linked item into the ordering table. */
s32 func_80024A1C(void *first_item)
{
    u16 screen_coords[3];
    void *list_item;
    void *item_data;
    GameWork *render_context;
    u8 *draw_mode;
    u8 *triangle;
    u32 depth_index;
    s32 point_index;
    s32 blend_mode;
    s32 byte_offset;
    u32 *ot_entry_base;
    u32 ot_tag;

    list_item = first_item;
    render_context = &g_game_work;

    do {
        item_data = list_item;
        point_index = 3;
        do {
            draw_mode = render_context->draw_buffer + 0x8D0;
            draw_mode = *(u8 **)draw_mode;
            *(u8 **)(render_context->draw_buffer + 0x8D0) = draw_mode + 0xC;

            triangle = *(u8 **)(render_context->draw_buffer + 0x8D0);
            *(u8 **)(render_context->draw_buffer + 0x8D0) = triangle + 0x14;

            ((TrailTriangle *)triangle)->unk_04 = ((TrailRenderItem *)item_data)->unk_48;
            func_80066690(triangle);
            func_80066640(triangle, 1);

            blend_mode = 3;
            if (((TrailRenderItem *)item_data)->unk_54 > 0) {
                blend_mode = 1;
            }
            func_80067F20(draw_mode, 0, 0,
                func_80066460(0, blend_mode, 0, 0) & 0xFFFF, 0);

            byte_offset = (point_index * 8) + 0x28;
            depth_index = func_80065420((u8 *)item_data + byte_offset,
                screen_coords, &screen_coords[2], &screen_coords[2]) - 8;

            ((TrailTriangle *)triangle)->unk_08 = screen_coords[0] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_0A = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_0C = screen_coords[0] - (func_80069EF8() & 1) - 1;
            ((TrailTriangle *)triangle)->unk_0E = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((TrailTriangle *)triangle)->unk_10 = screen_coords[0] + (func_80069EF8() & 4) - 2;
            ((TrailTriangle *)triangle)->unk_12 = screen_coords[1] - (func_80069EF8() & 1) - 1;

            if (depth_index < 0x1E0U) {
                u32 addr_mask = 0x00FFFFFF;
                u32 length_mask = 0xFF000000;

                byte_offset = depth_index * 4;
                ((GpuLinkTag *)triangle)->addr = ((GpuLinkTag *)&((u32 *)(render_context->draw_buffer + 0xB0))[depth_index])->addr;
                ot_entry_base = (u32 *)(byte_offset + (s32) render_context->draw_buffer);
                ot_tag = ((TrailOrderEntry *)ot_entry_base)->unk_B0;
                (*(u32 *)((u8 *)ot_entry_base + 0xB0)) = (ot_tag & length_mask) |
                    ((u32)triangle & addr_mask);

                (*(u32 *)((u8 *)draw_mode + 0)) =
                    (((TrailDrawMode *)draw_mode)->unk_00 & length_mask) |
                    (((u32 *)(render_context->draw_buffer + 0xB0))[depth_index] & addr_mask);
                ((u32 *)(render_context->draw_buffer + 0xB0))[depth_index] =
                    (((u32 *)(render_context->draw_buffer + 0xB0))[depth_index] & length_mask) |
                    ((u32)draw_mode & addr_mask);
            }
            point_index--;
        } while (point_index >= 0);

        if (((TrailChainPrefix *)list_item)[-1].unk_00 == 0) break;
        list_item = (void *)(((TrailChainPrefix *)list_item)[-1].unk_00 + 0x20);
    } while (1);

    return 0;
}
