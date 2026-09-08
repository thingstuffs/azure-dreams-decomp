#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80170D58_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80170D58_0;   /* arg1 in func_80170D58 */

typedef struct S_80170D58_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0xA];
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0x2A];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_80170D58_1;   /* arg0 in func_80170D58 */




extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

/* Update motion with collision checks, grow the sprite, and flag expired objects. */
void func_80170D58(void *motion, void *position, void *sprite)
{
    s32 height;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 life_ticks;

    ((S_80170D58_0 *)position)->unk_00.at00.v += ((S_80170D58_1 *)motion)->unk_54;
    ((S_80170D58_1 *)motion)->unk_54 += ((S_80170D58_1 *)motion)->unk_60;
    if ((func_800BCB04(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                       ((S_80170D58_0 *)position)->unk_08.at02.v) < 0x200) &&
        ((s16)func_800A45D8(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                            ((S_80170D58_0 *)position)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)position)->unk_00.at00.v -= ((S_80170D58_1 *)motion)->unk_54;
        ((S_80170D58_1 *)motion)->unk_54 = 0;
        ((S_80170D58_1 *)motion)->unk_60 = 0;
    }

    ((S_80170D58_0 *)position)->unk_04.at00.v += ((S_80170D58_1 *)motion)->unk_58;
    ((S_80170D58_1 *)motion)->unk_58 += ((S_80170D58_1 *)motion)->unk_64;
    if ((func_800BCB04(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                       ((S_80170D58_0 *)position)->unk_08.at02.v) < 0x200) &&
        ((s16)func_800A45D8(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                            ((S_80170D58_0 *)position)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)position)->unk_04.at00.v -= ((S_80170D58_1 *)motion)->unk_58;
        ((S_80170D58_1 *)motion)->unk_58 = 0;
        ((S_80170D58_1 *)motion)->unk_64 = 0;
    }

    ((S_80170D58_0 *)position)->unk_08.at00.v += ((S_80170D58_1 *)motion)->unk_5C;
    ((S_80170D58_1 *)motion)->unk_5C += ((S_80170D58_1 *)motion)->unk_68;
    height = ((S_80170D58_0 *)position)->unk_08.at02.v;
    if (func_800BCB04(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                      (s16)(((S_80170D58_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_80170D58_1 *)motion)->unk_5C = 0;
        ((S_80170D58_0 *)position)->unk_08.at02.v =
            func_800BCB04(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                          (s16)(((S_80170D58_0 *)position)->unk_08.at02u.v - 4)) - 0x11;
        ((S_80170D58_0 *)position)->unk_08.at00u.v = 0;
        if (((S_80170D58_1 *)motion)->unk_1A == 0) {
            ((S_80170D58_1 *)motion)->unk_1A = 1;
            ((S_80170D58_1 *)motion)->unk_26.s = 0;
        }
    }

    frame_count = ((S_80170D58_1 *)motion)->unk_28 + 1;
    ((S_80170D58_1 *)motion)->unk_28 = frame_count;
    if ((frame_count & 3) == 0) {
        func_800478B8(sprite);
    }

    scale_x = ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v + 0x64;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = scale_x;
    if (scale_x > 0x1000) {
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = 0x1000;
    }

    scale_y = ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v + 0x64;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = scale_y;
    if (scale_y > 0x1000) {
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = 0x1000;
    }

    life_ticks = ((S_80170D58_1 *)motion)->unk_26.u - 1;
    ((S_80170D58_1 *)motion)->unk_26.u = life_ticks;
    if ((s16)life_ticks <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
