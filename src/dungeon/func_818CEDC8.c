#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818CEDC8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_818CEDC8_0;   /* arg1 in func_818CEDC8 */

typedef struct S_818CEDC8_1_pre {
    u16 unk_00;
} S_818CEDC8_1_pre;   /* the 0x2 bytes before arg0 in func_818CEDC8, addressed as arg0[-1] */

typedef struct S_818CEDC8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x42];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818CEDC8_1;   /* arg0 in func_818CEDC8 */



extern s16 D_80025924[5];
extern s32 D_800814A0[3];
s32 rand();
s32 func_800A45D8();
s16 func_800BCB04();

/* Updates effect motion, collisions, animation, scale, and expiration. */
void func_818CEDC8(void *state, S_818CEDC8_0 *position, Rec_D_80082E80 *sprite) {
    s32 current_z;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 life_left;
    s32 collision_z;

    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((S_818CEDC8_1 *)state)->unk_4C);
    ((S_818CEDC8_1 *)state)->unk_4C = (s32) (((S_818CEDC8_1 *)state)->unk_4C + ((S_818CEDC8_1 *)state)->unk_58);
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v,
                       (collision_z = position->unk_08.at02.v, *D_80025924 = 1, collision_z)) << 0x10) != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v - ((S_818CEDC8_1 *)state)->unk_4C);
        ((S_818CEDC8_1 *)state)->unk_4C = 0;
        ((S_818CEDC8_1 *)state)->unk_58 = 0;
    }
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((S_818CEDC8_1 *)state)->unk_50);
    ((S_818CEDC8_1 *)state)->unk_50 = (s32) (((S_818CEDC8_1 *)state)->unk_50 + ((S_818CEDC8_1 *)state)->unk_5C);
    if ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0) {
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v - ((S_818CEDC8_1 *)state)->unk_50);
        ((S_818CEDC8_1 *)state)->unk_50 = 0;
        ((S_818CEDC8_1 *)state)->unk_5C = 0;
    }
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((S_818CEDC8_1 *)state)->unk_54);
    {
        s32 accel_z = ((S_818CEDC8_1 *)state)->unk_60;
        ((S_818CEDC8_1 *)state)->unk_54 += accel_z;
    }
    ((S_818CEDC8_1 *)state)->unk_4C = (s32) ((((S_818CEDC8_1 *)state)->unk_4C * 0x60) / 100);
    ((S_818CEDC8_1 *)state)->unk_50 = (s32) ((((S_818CEDC8_1 *)state)->unk_50 * 0x60) / 100);
    current_z = position->unk_08.at02.v;
    if ((func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02u.v - 4)) - 0x10) < current_z) {
        ((S_818CEDC8_1 *)state)->unk_54 = 0;
        position->unk_08.at02.v = (s16) (func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02.v - 4)) - 0x11);
        position->unk_08.at00u.v = 0;
        if (((S_818CEDC8_1 *)state)->unk_08 == 0) {
            ((S_818CEDC8_1 *)state)->unk_08 = 1;
            ((S_818CEDC8_1 *)state)->unk_4C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
            ((S_818CEDC8_1 *)state)->unk_50 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
        }
    }
    frame_count = ((S_818CEDC8_1 *)state)->unk_04 + 1;
    ((S_818CEDC8_1 *)state)->unk_04 = frame_count;
    if (!(frame_count & 3)) {
        func_800478B8(sprite);
    }
    scale_x = sprite->unk_1C.at00_u16.v + 0x64;
    sprite->unk_1C.at00_u16.v = scale_x;
    if ((u32) (scale_x & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at00_u16.v = 0x1000U;
    }
    scale_y = sprite->unk_1C.at02_u16.v + 0x64;
    sprite->unk_1C.at02_u16.v = scale_y;
    if ((u32) (scale_y & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at02_u16.v = 0x1000U;
    }
    life_left = ((S_818CEDC8_1 *)state)->unk_02 - 1;
    ((S_818CEDC8_1 *)state)->unk_02 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        ((S_818CEDC8_1_pre *)state)[-1].unk_00 = (u16) (((S_818CEDC8_1_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
