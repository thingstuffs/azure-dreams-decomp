#include "common.h"

typedef struct S_func_818C8FD0_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    union { s16 s16; u16 u16; } unk_0A;
    u8 pad_0C[0x72];
    union { s16 s16; u16 u16; } unk_7E;
    u8 pad_80[2];
    u16 unk_82;
    union { s16 s16; u16 u16; } unk_84;
    s16 unk_86;
    s16 unk_88;
    u8 pad_8A[0x16];
    u8 unk_A0;
    u8 unk_A1;
    u8 pad_A2[6];
    void *unk_A8;
    void *unk_AC;
} S_func_818C8FD0_1;

typedef struct S_func_818C8FD0_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { s32 s32; void *ptr; } unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_func_818C8FD0_2;

typedef struct S_func_818C8FD0_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_func_818C8FD0_3;

typedef struct S_func_818C8FD0_4 {
    union { s32 s32; struct { u8 pad_00[2]; u16 unk_02; } u16; } unk_00;
    union { s32 s32; struct { u8 pad_04[2]; u16 unk_06; } u16; } unk_04;
    union { s32 s32; struct { u8 pad_08[2]; u16 unk_0A; } u16; } unk_08;
} S_func_818C8FD0_4;

typedef struct S_func_818C8FD0_5 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818C8FD0_5;

typedef struct S_func_818C8FD0_6 {
    u8 pad_00[8];
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
} S_func_818C8FD0_6;

typedef struct S_func_818C8FD0_7 {
    u8 pad_00[2];
    union { s16 s16; u16 u16; } unk_02;
    u8 pad_04[4];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    void *unk_2C;
    s32 unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_func_818C8FD0_7;

typedef struct S_func_818C8FD0_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_818C8FD0_8;

typedef struct S_func_818C8FD0_9 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_func_818C8FD0_9;

typedef struct S_func_818C8FD0_10 {
    u16 unk_00;
} S_func_818C8FD0_10;


typedef struct OffsetTable {
    u8 value[32];
} OffsetTable;

extern OffsetTable D_80024004;
extern void D_80024270(void);
extern s16 D_80024D04[5];
extern s8 D_8006CCD8[9];
extern s8 D_8006CCE8[9];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800DEC00[];

extern void func_8003DB94(void *, void *, s32);
extern void *func_8003DF74(void *, void *, void *, s32);
extern void *func_8003FC64(s32);








/* Updates an effect through attachment, motion, and timed cleanup. */
void func_818C8FD0(S_func_818C8FD0_1 *state, S_func_818C8FD0_4 *output_pos, S_func_818C8FD0_5 *part)
{
    s16 delta[3];
    s32 mode;
    u16 angle;
    u16 frame_count;
    OffsetTable offsets;
    S_func_818C8FD0_2 *object;
    S_func_818C8FD0_3 *owner_node;
    S_func_818C8FD0_4 *owner_pos;
    S_func_818C8FD0_3 *effect_node;
    S_func_818C8FD0_4 *effect_pos;
    OffsetTable *offset_table;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 one;
    OffsetTable *offset_source = &D_80024004;

    object = state->unk_00;
    offsets = *offset_source;
    offset_table = &offsets;
    one = 1;
    frame_count = state->unk_82;
    mode = state->unk_0A.s16;
    owner_node = (S_func_818C8FD0_3 *)((u8 *)object - 0x20);
    owner_pos = owner_node->unk_08;
    frame_count++;
    state->unk_82 = frame_count;

    if (mode == one)
        goto mode1;
    if (mode < 2) {
        if (mode == 0)
            goto mode0;
        return;
    }
    if (mode == 2)
        goto mode2;
    if (mode == 3) {
        goto mode3;
    }
    return;

mode0:
    part->unk_0C = 0x00808080;
    part->unk_1E = 0x1000;
    part->unk_1C = 0x1000;
    func_8003DB94(part, D_800DEC00, 0);
    angle = object->unk_2A;
    D_80024D04[0] = one;
    state->unk_7E.s16 = (angle >> 9) & 7;
    ((volatile S_func_818C8FD0_1 *)state)->unk_0A.u16++;

mode1:
    {
        S_func_818C8FD0_6 *owner_part;
        u16 position_z;
        u16 final_z;
        u16 delta_z;

        owner_part = owner_node->unk_0C;

        if ((func_8003DF74(owner_part->unk_08, owner_part, delta, 0) != 0) ||
            (((S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
            output_pos->unk_00.u16.unk_02 = owner_pos->unk_00.u16.unk_02;
            output_pos->unk_04.u16.unk_06 = owner_pos->unk_04.u16.unk_06;
            position_z = owner_pos->unk_08.u16.unk_0A;
            output_pos->unk_08.u16.unk_0A = position_z;

            if (!(((S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
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

            if (((S_func_818C8FD0_10 *)state->unk_04)->unk_00 & 0x80) {
                state->unk_84.s16 = 0;
                state->unk_0A.u16++;
                return;
            }
        }
        return;
    }

mode2:
    {

        effect_node = func_8003FC64(0x12);

        if (effect_node != 0) {
            S_func_818C8FD0_7 *effect;
            s32 direction_index;
            S_func_818C8FD0_8 *tile;

            effect = (S_func_818C8FD0_7 *)((u8 *)effect_node + 0x20);

            {
                s16 *direction_offset;

                direction_index = state->unk_7E.s16;
                direction_offset = (s16 *)((u8 *)offset_table + direction_index * 4);
                effect->unk_58 = (s32)direction_offset[0] << 16;
            }
            {
                u16 *direction_offset;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

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
                u8 *table_base = (u8 *)D_8006CCD8;

                direction_index = state->unk_7E.s16 * 2;
                tile = ((S_func_818C8FD0_3 *)((u8 *)object - 0x20))->unk_0C;
                state->unk_A0 =
                    tile->unk_24 + table_base[direction_index];
            }
            {
                u8 *table_base = (u8 *)D_8006CCE8;

                direction_index = state->unk_7E.s16 * 2;
                state->unk_A1 =
                    tile->unk_25 + table_base[direction_index];
            }

            if (object->unk_60.ptr != 0) {
                register s32 tile_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s32 duration;
                S_func_818C8FD0_4 *target_pos;
                u16 end_time;

                effect->unk_08 = one;
                if (object->unk_72 != tile->unk_24) {
                    tile_distance = object->unk_72 - tile->unk_24;
                } else {
                    tile_distance = object->unk_73;
                    tile_distance -= tile->unk_25;
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                    effect->unk_02.s16 = tile_distance * 2;
                } else {
                    effect->unk_02.s16 = tile_distance * 2;
                }

                target_pos = ((S_func_818C8FD0_3 *)((u8 *)object->unk_60.ptr - 0x20))->unk_08;
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

            effect_node->unk_10 = D_80024270;
            {
                effect_pos = effect_node->unk_08;

                effect_pos->unk_00.s32 = output_pos->unk_00.s32;
                effect_pos->unk_04.s32 = output_pos->unk_04.s32;
                effect_pos->unk_08.s32 = output_pos->unk_08.s32;
                {
                    S_func_818C8FD0_9 *effect_part = effect_node->unk_0C;

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

mode3:
    if (state->unk_88 == 0x63) {
        effect_node = state->unk_A8;
        effect_pos = state->unk_AC;

        if (effect_node->unk_1E & 0x8000) {
            state->unk_88 = 0;
            goto finish;
        }
        output_pos->unk_00.s32 = effect_pos->unk_00.s32;
        output_pos->unk_04.s32 = effect_pos->unk_04.s32;
        output_pos->unk_08.s32 = effect_pos->unk_08.s32;
    }
    goto finish;

finish:
    {
        u16 old_timer = state->unk_84.u16;
        s16 timer = old_timer + 1;

        state->unk_84.u16 = timer;
        if (state->unk_86 < timer) {
            s32 active_flag = D_80024D04[0];

            state->unk_84.u16 = old_timer;
            if (active_flag == 0) {
                D_8008346C[0] = 0;
                ((S_func_818C8FD0_10 *)((u8 *)state - 2))->unk_00 |= 0x8000;
                D_800814A0[0] |= 0x8000;
                return;
            } else {
                D_80024D04[0] = 0;
            }
        }
    }
}
