#include "modules/dungeon_ovl_18d0850.h"

s32 func_8002443C(s32 owner, void *origin, s16 motion, s16 frame) {
    M2C_UNK *node_type;
    u16 position_z;
    s32 angle;
    ovl_18d0850_818B0C3C_S_8002443C_3 *sprite;
    s32 result;
    u8 *position;
    u8 *node;
    s16 frame_index = frame;
    s32 sprite_mode;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        node_type = (void *)dungeonAdvanceHeightOffsetAndPlacement;
        ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_20 = owner;
        owner = (s32)(node + 0x20);
        ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_10 = node_type;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_04 = motion;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_06 = (s16) (-6 - (func_80069EF8() % 5));
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_08 = (u16) ((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_02.s;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0A = (u16) ((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_06.s;
        node_type = (M2C_UNK *)(((ovl_18d0850_818B0C3C_S_8002443C_2 *)origin)->unk_0A.s);
        sprite_mode = 0x7E09;
        ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0C = (u16)node_type;
        sprite = ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_0C;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_12 = (s16)sprite_mode;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        func_8003DB94(sprite, &D_800DEC70, (s16)frame_index % 16, (s16)frame_index);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8004491C(node, func_80045340);
        position = ((ovl_18d0850_818B0C3C_S_8002443C_0 *)node)->unk_08;
        angle = func_80069EF8() % 0x1000;
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_02.u = (s16) (((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_06.u = (s16) (((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        position_z = ((ovl_18d0850_818B0C3C_S_8002443C_1 *)owner)->unk_0C;
        result = (s32)node;
        ((ovl_18d0850_818B0C3C_S_8002443C_2 *)position)->unk_0A.u = (s16)position_z;
        return result;
    }
    result = 0;
    return result;
}
