#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002443C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8002443C_0;   /* work_s3 in func_8002443C */

typedef struct S_8002443C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_8002443C_1;   /* work_s1 in func_8002443C */

typedef struct S_8002443C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_8002443C_2;   /* work_s2 in func_8002443C */

typedef struct S_8002443C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002443C_3;   /* temp_s0 in func_8002443C */


M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
extern M2C_UNK D_800242E0;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;

/* Creates a sprite node with a randomized offset from the supplied origin. */
s32 func_8002443C(s32 owner, void *origin, s16 motion, s32 frame) {
    M2C_UNK *node_type;
    u16 position_z;
    s32 angle;
    S_8002443C_3 *sprite;
    s32 result;
    u8 *position;
    u8 *node;
    s16 frame_index = frame;
    s32 sprite_mode;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        node_type = &D_800242E0;
        ((S_8002443C_0 *)node)->unk_20 = owner;
        owner = (s32)(node + 0x20);
        ((S_8002443C_0 *)node)->unk_10 = node_type;
        ((S_8002443C_1 *)owner)->unk_04 = motion;
        ((S_8002443C_1 *)owner)->unk_06 = (s16) (-6 - (func_80069EF8() % 5));
        ((S_8002443C_1 *)owner)->unk_08 = (u16) ((S_8002443C_2 *)origin)->unk_02.s;
        ((S_8002443C_1 *)owner)->unk_0A = (u16) ((S_8002443C_2 *)origin)->unk_06.s;
        node_type = (M2C_UNK *)(((S_8002443C_2 *)origin)->unk_0A.s);
        sprite_mode = 0x7E09;
        ((S_8002443C_1 *)owner)->unk_0C = (u16)node_type;
        sprite = ((S_8002443C_0 *)node)->unk_0C;
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
        func_8004491C(node, &D_80045340);
        position = ((S_8002443C_0 *)node)->unk_08;
        angle = func_80069EF8() % 0x1000;
        ((S_8002443C_2 *)position)->unk_02.u = (s16) (((S_8002443C_1 *)owner)->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        ((S_8002443C_2 *)position)->unk_06.u = (s16) (((S_8002443C_1 *)owner)->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        position_z = ((S_8002443C_1 *)owner)->unk_0C;
        result = (s32)node;
        ((S_8002443C_2 *)position)->unk_0A.u = (s16)position_z;
        return result;
    }
    result = 0;
    return result;
}
