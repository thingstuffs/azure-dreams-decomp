#include "shared/object_node.h"
#include "modules/dungeon_ovl_18e8800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
























extern u8 D_800DEC00[];









/* Updates an effect through attachment, motion, and timed cleanup. */
void func_800247D0(B31_818C8FD0_S_func_818C8FD0_1 *state, B31_818C8FD0_S_func_818C8FD0_4 *output_pos, B31_818C8FD0_S_func_818C8FD0_5 *part)
{
    s16 delta[3];
    s32 mode;
    u16 angle;
    u16 frame_count;
    B31_818C8FD0_OffsetTable offsets;
    B31_818C8FD0_S_func_818C8FD0_2 *object;
    B31_818C8FD0_S_func_818C8FD0_3 *owner_node;
    B31_818C8FD0_S_func_818C8FD0_4 *owner_pos;
    B31_818C8FD0_S_func_818C8FD0_3 *effect_node;
    B31_818C8FD0_S_func_818C8FD0_4 *effect_pos;
    B31_818C8FD0_OffsetTable *offset_table;
    s32 one;
    B31_818C8FD0_OffsetTable *offset_source = &D_80024004;

    object = state->unk_00;
    offsets = *offset_source;
    offset_table = &offsets;
    one = 1;
    frame_count = state->unk_82;
    mode = state->unk_0A.s16;
    owner_node = (B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object - 0x20);
    owner_pos = owner_node->unk_08;
    frame_count++;
    state->unk_82 = frame_count;

    switch (mode) {
    case 0:
        part->unk_0C = 0x00808080;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        func_8003DB94(part, D_800DEC00, 0);
        angle = object->unk_2A;
        D_80024D04 = one;
        state->unk_7E.s16 = (angle >> 9) & 7;
        state->unk_0A.u16++;
    case 1:
        {
            B31_818C8FD0_S_func_818C8FD0_6 *owner_part;
            u16 position_z;
            u16 final_z;
            u16 delta_z;

            owner_part = owner_node->unk_0C;

            if ((func_8003DF74(owner_part->unk_08, owner_part, delta, 0) != 0) ||
                (((B31_818C8FD0_S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
                output_pos->unk_00.u16.unk_02 = owner_pos->unk_00.u16.unk_02;
                output_pos->unk_04.u16.unk_06 = owner_pos->unk_04.u16.unk_06;
                position_z = owner_pos->unk_08.u16.unk_0A;
                output_pos->unk_08.u16.unk_0A = position_z;

                if (!(((B31_818C8FD0_S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
                    output_pos->unk_00.u16.unk_02 += (u16)delta[0];
                    output_pos->unk_04.u16.unk_06 += (u16)delta[1];
                    final_z = output_pos->unk_08.u16.unk_0A;
                    delta_z = (u16)delta[2];
                    final_z += delta_z;
                    output_pos->unk_08.u16.unk_0A = final_z;
                } else {
                    final_z = position_z - 0x40;
                    output_pos->unk_08.u16.unk_0A = final_z;
                }

                if (((B31_818C8FD0_S_func_818C8FD0_10 *)state->unk_04)->unk_00 & 0x80) {
                    state->unk_84.s16 = 0;
                    state->unk_0A.u16++;
                    return;
                }
            }
            return;
        }
    case 2:
        {

            effect_node = func_8003FC64(0x12);

            if (effect_node != 0) {
                B31_818C8FD0_S_func_818C8FD0_7 *effect;
                s32 direction_index;
                B31_818C8FD0_S_func_818C8FD0_8 *tile;

                effect = (B31_818C8FD0_S_func_818C8FD0_7 *)((u8 *)effect_node + 0x20);

                {
                    s16 *direction_offset;

                    direction_index = state->unk_7E.s16;
                    direction_offset = (s16 *)((u8 *)offset_table + direction_index * 4);
                    effect->unk_58 = (s32)direction_offset[0] << 16;
                }
                {
                    u16 *direction_offset;

                    direction_index = state->unk_7E.s16;
                    direction_offset = (u16 *)((u8 *)offset_table + direction_index * 4);
                    effect->unk_5C = (s32)direction_offset[1] << 16;
                }
                effect->unk_2C = object;
                effect->unk_30 = object->unk_60.s32;
                effect->unk_0A = (state->unk_84.s16 - 1) / 2;
                effect->unk_15 = state->unk_09;
                effect->unk_16 = state->unk_7E.u16;

                {
                    u8 *table_base = (u8 *)((s8 *)dirStepX);

                    direction_index = state->unk_7E.s16 * 2;
                    tile = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object - 0x20))->unk_0C;
                    state->unk_A0 =
                        tile->unk_24 + table_base[direction_index];
                }
                {
                    u8 *table_base = (u8 *)((s8 *)dirStepY);

                    direction_index = state->unk_7E.s16 * 2;
                    state->unk_A1 =
                        tile->unk_25 + table_base[direction_index];
                }

                if (object->unk_60.ptr != 0) {
                    s32 tile_distance;
                    s32 duration;
                    B31_818C8FD0_S_func_818C8FD0_4 *target_pos;
                    u16 end_time;
                    u32 tile_coord;

                    effect->unk_08 = one;
                    tile_distance = object->unk_72;
                    tile_coord = tile->unk_24;
                    if (tile_distance != tile_coord) {
                        tile_distance -= tile_coord;
                    } else {
                        tile_distance = object->unk_73;
                        tile_coord = tile->unk_25;
                        tile_distance -= tile_coord;
                    }
                    if (tile_distance < 0) {
                        tile_distance = -tile_distance;
                        effect->unk_02.s16 = tile_distance * 2;
                    } else {
                        effect->unk_02.s16 = tile_distance * 2;
                    }

                    target_pos = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object->unk_60.ptr - 0x20))->unk_08;
                    duration = effect->unk_02.s16;
                    if (duration != 0) {
                        effect->unk_60 =
                            (target_pos->unk_08.s32 - output_pos->unk_08.s32 - 0x200000) /
                            (duration - 1);
                    }
                    end_time = effect->unk_02.u16;
                    end_time += 0x3C;
                    state->unk_86 = end_time;
                } else {
                    effect->unk_02.s16 = 0x20;
                    effect->unk_08 = 0;
                    state->unk_86 = effect->unk_02.s16 + 0x1E;
                }

                effect_node->unk_10 = func_80024270;
                {
                    effect_pos = effect_node->unk_08;

                    effect_pos->unk_00.s32 = output_pos->unk_00.s32;
                    effect_pos->unk_04.s32 = output_pos->unk_04.s32;
                    effect_pos->unk_08.s32 = output_pos->unk_08.s32;
                    {
                        B31_818C8FD0_S_func_818C8FD0_9 *effect_part = effect_node->unk_0C;

                        effect_part->unk_0E = 0x80;
                        effect_part->unk_0D = 0x80;
                        effect_part->unk_0C = 0x80;
                        effect_part->unk_1E = 0x1000;
                        effect_part->unk_1C = 0x1000;
                    }
                    state->unk_A8 = effect_node;
                    state->unk_AC = effect_pos;
                    state->unk_88 = 0x63;
                }
            }
            state->unk_0A.u16++;
            return;
        }
    case 3:
        if (state->unk_88 == 0x63) {
            effect_node = state->unk_A8;
            effect_pos = state->unk_AC;

            if (effect_node->unk_1E & 0x8000) {
                state->unk_88 = 0;
            } else {
                output_pos->unk_00.s32 = effect_pos->unk_00.s32;
                output_pos->unk_04.s32 = effect_pos->unk_04.s32;
                output_pos->unk_08.s32 = effect_pos->unk_08.s32;
            }
        }
        break;
    default:
        return;
    }

    {
        u16 old_timer = state->unk_84.u16;
        s16 timer = old_timer + 1;

        state->unk_84.u16 = timer;
        if (state->unk_86 < timer) {
            s32 active_flag = D_80024D04;

            state->unk_84.u16 = old_timer;
            if (active_flag == 0) {
                dungeonStatus.unk_0C = 0;
                ((B31_818C8FD0_S_func_818C8FD0_10 *)((u8 *)state - 2))->unk_00 |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
                return;
            } else {
                D_80024D04 = 0;
            }
        }
    }
}
