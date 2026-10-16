#include "modules/dungeon_ovl_18d0850.h"

void dungeonUpdateMovementTowardChildTerrainTargetAnimatesAssociatedEffects(ovl_18d0850_818B1664_State *state_arg, ovl_18d0850_818B1664_Motion *motion_arg, ovl_18d0850_818B1664_DrawInfo *draw_info)
{
    ovl_18d0850_818B1664_WorkFrame work;
    u16 saved_y;
    ovl_18d0850_818B1664_DrawInfo *draw = draw_info;
    ovl_18d0850_818B1664_Entity *entity;
    ovl_18d0850_818B1664_EntityHeader *header;
    s32 dispatch_state;
    s32 direction;
    s32 color;
    u16 source_z;
    ovl_18d0850_818B1664_TargetInfo *target_info;
    ovl_18d0850_818B1664_Motion *step_x;
    u8 *angle_update;
    u8 *angle_clear;
    u8 *angle_build;
    u8 *effect_clear;
    ovl_18d0850_818B1664_Effect **effect_create;
    ovl_18d0850_818B1664_Effect **effect_grow;
    ovl_18d0850_818B1664_Effect **effect_shrink;
    ovl_18d0850_818B1664_Effect **effect_cleanup;
    s32 index;
    s32 next_state;
    s32 angle;
    s32 effect_angle;
    s32 effect_step;
    s32 collision_result;
    s32 terrain_height;
    s16 *target_cursor;
    s16 *distance_cursor;
    s32 target_x;
    s32 target_y;
    u16 angle_raw;
    s32 angle_signed;
    s32 angle_adjusted;
    u16 lowered_z;
    s16 *step_y;
    s32 target;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    u16 final_x;

    void *cleanup_base;

    index = 7;
    angle_update = (u8 *)state_arg + 14;
    entity = state_arg->entity;
loop_0:
    {
        angle_raw = *(u16 *)(angle_update + 26) + (u16)state_arg->angleStep;
        angle_signed = (s16)angle_raw;
        angle_adjusted = angle_signed;
        *(u16 *)(angle_update + 26) = angle_raw;
        angle_raw = angle_signed - (((angle_adjusted / 128)) << 7);
        *(u16 *)(angle_update + 26) = angle_raw;
        index--;
        angle_update -= 2;
    }
    if (index >= 0)
        goto loop_0;
    {
        s32 timer_value;

        timer_value = (u16)state_arg->timer;
        timer_value++;
        state_arg->timer = timer_value;
        timer_value = (u16)state_arg->timer2;
        dispatch_state = state_arg->state;
        timer_value++;
        state_arg->timer2 = timer_value;
    }

    switch (dispatch_state) {
    case 0:
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        state_arg->angleStep = 4;
        state_arg->state++;
        index = 7;
        angle_clear = (u8 *)state_arg + 14;
        do {
            *(s16 *)(angle_clear + 26) = 0;
            index--;
            angle_clear -= 2;
        } while (index >= 0);
        index = 9;
        effect_clear = (u8 *)state_arg + 36;
        do {
            *(ovl_18d0850_818B1664_Effect **)(effect_clear + 44) = 0;
            index--;
            effect_clear -= 4;
        } while (index >= 0);
        func_800240EC(angle_clear, angle_update, draw_info);
        color = 0x00808080;
        direction = (entity->flags2A >> 9) & 7;
        state_arg->direction = direction;
        draw->color = color;

    case 1:
        header = (ovl_18d0850_818B1664_EntityHeader *)((u8 *)entity - 0x20);
        target_info = header->info;
        if (resolveRecordOrientationOrFallback(target_info->map, target_info, work.distance, 0) == 0) {
            if (!(header->info->flags & 0x8000)) {
                break;
            }
        }

        step_x = header->position;
        motion_arg->x.half.hi = step_x->x.half.hi;
        motion_arg->y.half.hi = step_x->y.half.hi;
        source_z = step_x->z.half.hi;
        motion_arg->z.half.hi = source_z;
        if (!(header->info->flags & 0x8000)) {
            motion_arg->x.half.hi += work.distance[0];
            motion_arg->y.half.hi += work.distance[1];
            motion_arg->z.half.hi += work.distance[2];
        } else {
            lowered_z = source_z - 64;
            motion_arg->z.half.hi = lowered_z;
        }

        if (!(state_arg->flags & 1)) {
            func_8004491C((u8 *)state_arg - 0x20, func_80024DF4);
            state_arg->flags |= 1;
        }
        if (!(state_arg->resource->flags & 0x80)) {
            break;
        }

        index = 0;
        if (entity->child != 0) {
            cleanup_base = (void *)(*(ovl_18d0850_818B1664_Motion **)((u8 *)entity->child - 0x18));

            color = motion_arg->x.half.hi;
            work.distance[0] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi - color);
            work.distance[1] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi - motion_arg->y.half.hi);
            if (entity->child->flags & 0x40000) {
                color = motion_arg->z.half.hi;
                color -= 16;
                work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - color);
            } else {
                work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - motion_arg->z.half.hi);
            }
            index = 1;

            state_arg->duration = work.distance[0];
            distance_cursor = &work.target.x.half.hi;
            do {
                if (distance_cursor[12] > state_arg->duration) {
                    state_arg->duration = (u16)distance_cursor[12];
                }
                index++;
                distance_cursor++;
            } while (index < 3);
            state_arg->duration >>= 5;
            if (state_arg->duration == 0) {
                state_arg->duration = 1;
            }

            motion_arg->dx.half.hi =
                (((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi - motion_arg->x.half.hi) / state_arg->duration;
            motion_arg->dy.half.hi =
                (((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi - motion_arg->y.half.hi) / state_arg->duration;
            if (entity->child->flags & 0x40000) {
                s32 coord;
                coord = motion_arg->z.half.hi - 16;
                motion_arg->dz.half.hi =
                    (((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - coord) / state_arg->duration;
            } else {
                motion_arg->dz.half.hi =
                    (((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi - motion_arg->z.half.hi) /
                    state_arg->duration;
            }
            next_state = (u16)state_arg->state + 1;
            goto reset_state;
        }

        {
            ovl_18d0850_818B1664_TargetInfo *tile_info;

            tile_info = header->info;
            tile_x = tile_info->tileX;
            tile_y = tile_info->tileY;
        }
        final_x = tile_x;
        saved_y = tile_y;

        while (index < 8) {
            grid_x = (s16)tile_x;
            grid_y = (s16)tile_y;
            collision_result = dungeonCheckLayerOffsetHeight(
                (grid_x << 6) & 0xFFC0,
                (grid_y << 6) & 0xFFC0,
                entity->height,
                (s16)(state_arg->direction << 9));
            if ((s16)collision_result != 0) {
                break;
            }
            step_x = (ovl_18d0850_818B1664_Motion *)&dirStepX[state_arg->direction];
            target = (u16)entity->height;
            target -= 32;
            target = (u32)target << 16;
            target >>= 16;
            step_y = &dirStepY[state_arg->direction];
            terrain_height = func_800BCB04(
                ((grid_x + *(s16 *)step_x) << 6) + 32 & 0xFFE0,
                ((grid_y + *step_y) << 6) + 32 & 0xFFE0,
                target);
            if ((s16)terrain_height >= 513 ||
                (s16)(terrain_height - entity->height) < -63) {
                break;
            }
            index++;
            tile_x += dirStepX[state_arg->direction];
            tile_y += dirStepY[state_arg->direction];
            saved_y = tile_y;
            final_x = tile_x;
        }

        target = (s32)(&work.target);
        index = 1;
        target_cursor = &work.target.x.half.hi;
        target_x = ((final_x << 16) >> 10) + ((dirStepX[state_arg->direction] + 1) << 5);
        ((ovl_18d0850_818B1664_Motion *)target)->x.half.hi = target_x;
        target_y = ((saved_y << 16) >> 10) + ((dirStepY[state_arg->direction] + 1) << 5);
        ((ovl_18d0850_818B1664_Motion *)target)->y.half.hi = target_y;
        ((ovl_18d0850_818B1664_Motion *)target)->z.half.hi = motion_arg->z.half.hi + 32;
        work.distance[0] = abs(((ovl_18d0850_818B1664_Motion *)target)->x.half.hi - motion_arg->x.half.hi);
        work.distance[1] = abs(((ovl_18d0850_818B1664_Motion *)target)->y.half.hi - motion_arg->y.half.hi);
        work.distance[2] = abs(((ovl_18d0850_818B1664_Motion *)target)->z.half.hi - motion_arg->z.half.hi);

        state_arg->duration = work.distance[0];
        do {
            if (target_cursor[12] > state_arg->duration) {
                state_arg->duration = (u16)target_cursor[12];
            }
            index++;
            target_cursor++;
        } while (index < 3);
        state_arg->duration >>= 5;
        if (state_arg->duration == 0) {
            state_arg->duration = 1;
        }
        motion_arg->dx.word = (((ovl_18d0850_818B1664_Motion *)target)->x.word - motion_arg->x.word) / state_arg->duration;
        motion_arg->dy.word = (((ovl_18d0850_818B1664_Motion *)target)->y.word - motion_arg->y.word) / state_arg->duration;
        motion_arg->dz.word = (((ovl_18d0850_818B1664_Motion *)target)->z.word - motion_arg->z.word) / state_arg->duration;
        state_arg->state = 8;
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        break;

    case 2:
        motion_arg->x.half.hi += motion_arg->dx.half.hi;
        motion_arg->y.half.hi += motion_arg->dy.half.hi;
        motion_arg->z.half.hi += motion_arg->dz.half.hi;
        dungeonCreateAnInitializedRenderStateCopyVector(state_arg, motion_arg);
        if (state_arg->timer < state_arg->duration) {
            break;
        }
        func_800A56E0(0x300);
        goto increment_reset;

    case 3:
        if (state_arg->timer < 8) {
            break;
        }
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        state_arg->state++;
        cleanup_base = (void *)(*(ovl_18d0850_818B1664_Motion **)((u8 *)entity->child - 0x18));
        motion_arg->x.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->x.half.hi;
        motion_arg->y.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->y.half.hi;
        if (entity->child->flags & 0x40000) {
            motion_arg->z.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi + 16;
        } else {
            motion_arg->z.half.hi = ((ovl_18d0850_818B1664_Motion *)cleanup_base)->z.half.hi;
        }

        index = 7;
        angle = 16;
        angle_build = (u8 *)state_arg + 14;
        do {
            *(s16 *)(angle_build + 26) = angle;
            angle += 16;
            index--;
            angle_build -= 2;
        } while (index > 0);
        state_arg->angles[0] = 0;

        index = 9;
        effect_create = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        effect_angle = (s32)0xFF1F0000;
create_loop:
        {
            effect_create[11] =
                func_8002443C(state_arg, motion_arg, effect_angle >> 16, index);
            effect_create--;
            effect_step = 0x190000;
            effect_angle += effect_step;
            index--;
        }
        if (index >= 0)
            goto create_loop;
        state_arg->field14 = 0;
        return;

    case 4:
    {
        ovl_18d0850_818B1664_Effect *effect;
        ovl_18d0850_818B1664_EffectInner *inner;
        s32 effect_delta;

        index = 9;
        effect_delta = 0x40404;
        effect_grow = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        do {
            effect = effect_grow[11];
            inner = effect->inner;
            inner->value += effect_delta;
            effect_grow--;
            index--;
        } while (index >= 0);
        if (state_arg->timer2 < 32) {
            break;
        }
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;
    }

    case 5:
        if (state_arg->timer2 < 32) {
            break;
        }
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;

    case 6:
    {
        ovl_18d0850_818B1664_Effect *effect;
        ovl_18d0850_818B1664_EffectInner *inner;
        ovl_18d0850_818B1664_Effect *cleanup_effect;
        s32 cleanup_flags;
        s32 global_flags;
        s32 effect_delta;

        index = 9;
        effect_delta = -0x40404;
        effect_shrink = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + 36);
        do {
            effect = effect_shrink[11];
            inner = effect->inner;
            inner->value += effect_delta;
            effect_shrink--;
            index--;
        } while (index >= 0);
        cleanup_base = entity;
        if (state_arg->timer2 < 32) {
            break;
        }
        func_80024050(((ovl_18d0850_818B1664_Entity *)cleanup_base)->child, state_arg->id);
        index = 9;
        cleanup_base = (void *)0x80080000;
        next_state = (u16)state_arg->state;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        do {
            effect_cleanup = (ovl_18d0850_818B1664_Effect **)((u8 *)state_arg + index * 4);
            cleanup_effect = effect_cleanup[11];
            if (cleanup_effect != 0) {
                cleanup_flags = cleanup_effect->flags;
                global_flags = *(s32 *)((u8 *)cleanup_base + 0x14A0);
                cleanup_flags |= 0x8000;
                global_flags |= 0x8000;
                cleanup_effect->flags = cleanup_flags;
                *(s32 *)((u8 *)cleanup_base + 0x14A0) = global_flags;
                effect_cleanup[11] = 0;
            }
            index--;
        } while (index >= 0);
        state_arg->field14 = 0;
        return;
    }

    case 7:
        if (state_arg->field14 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        *(u16 *)((u8 *)state_arg - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 8:
        motion_arg->x.half.hi += motion_arg->dx.half.hi;
        motion_arg->y.half.hi += motion_arg->dy.half.hi;
        motion_arg->z.half.hi += motion_arg->dz.half.hi;
        dungeonCreateAnInitializedRenderStateCopyVector(state_arg, motion_arg);
        if (state_arg->timer < state_arg->duration) {
            break;
        }

increment_reset:
        next_state = (u16)state_arg->state;
        state_arg->timer = 0;
        state_arg->timer2 = 0;
        next_state++;
        state_arg->state = next_state;
        break;

    case 9:
        if (state_arg->timer < 8) {
            break;
        }
        next_state = 7;
reset_state:
        state_arg->state = next_state;
        state_arg->timer = 0;
        state_arg->timer2 = 0;

    }
    state_arg->field14 = 0;
    return;
}
