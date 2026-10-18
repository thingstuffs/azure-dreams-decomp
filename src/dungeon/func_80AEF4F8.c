#include "modules/dungeon_resource10_slot0.h"

void func_80170CF8(
    R10_80170CF8_S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    void *node;
    R10_80170CF8_S_80AC55DC_2 *work;
    R10_80170CF8_S_80AC55DC_4 *sprite;
    u16 sprite_flags;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 t;

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((R10_80170CF8_S_80AC55DC_0 *)node)->unk_10 = ((u8 *)move_and_shrink_fading_effect);

        ((R10_80170CF8_S_80AC55DC_5 *)(((R10_80170CF8_S_80AC55DC_0 *)node)->unk_08))->unk_02 =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_02 + offset_x;
        ((R10_80170CF8_S_80AC55DC_5 *)(((R10_80170CF8_S_80AC55DC_0 *)node)->unk_08))->unk_06 =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_06 + offset_y;
        ((R10_80170CF8_S_80AC55DC_5 *)(((R10_80170CF8_S_80AC55DC_0 *)node)->unk_08))->unk_0A =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_0A + offset_z - 0x14;

        work = (R10_80170CF8_S_80AC55DC_2 *)((u8 *)node + 0x20);
        work->unk_36 = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_02;
        work->unk_38 = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_06;
        work->unk_3A = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_0A;
        step_x = -(offset_x << 16) / (duration / 8);
        work->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        work->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        t = step_z / 2;
        work->unk_48 = t;
        t = step_x;
        if (t < 0) {
            t += 3;
        }
        work->unk_4C = t >> 2;
        work->unk_50 = step_y / 4;
        work->unk_54 = step_z / 4;

        work->unk_14 = effect_id;
        work->unk_32 = duration;
        work->unk_34 = duration;
        func_8004491C(node, func_80045340);

        sprite = ((R10_80170CF8_S_80AC55DC_0 *)node)->unk_0C;
        sprite_flags = sprite->unk_14;
        sprite->unk_10 = 0x20;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_14 = sprite_flags | 0xC;
        ((R10_80170CF8_S_80AC55DC_0 *)node)->unk_20 = effect_value;
        work->unk_08 = effect_value;
        func_8003DB94(sprite, ((u8 *)D_800DEC70), 0);
    }
}

