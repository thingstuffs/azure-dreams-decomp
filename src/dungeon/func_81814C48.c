#include "common.h"

typedef struct S_81814C48_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81814C48_0;   /* arg1 in func_81814C48 */

typedef struct S_81814C48_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_81814C48_1;   /* arg0 in func_81814C48 */

typedef struct S_81814C48_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81814C48_2;   /* arg2 in func_81814C48 */



extern s32 rand();
extern s16 func_800BCB04();
extern s16 D_80025338;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;

void func_81814C48(void *arg0, void *arg1, void *arg2)
{
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 accum;
    s32 random;
    s32 call_a0;
    s32 call_a1;
    s32 call_a2;
    register s32 tail_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    call_a2 = (*(u16 *)((u8 *)arg1 + 0xA));
    call_a0 = ((S_81814C48_0 *)arg1)->unk_00.at02.v;
    call_a1 = ((S_81814C48_0 *)arg1)->unk_04.at02.v;
    D_80025338 = 1;
    if ((s16)((S_81814C48_0 *)arg1)->unk_08.at02.v <
        func_800BCB04(call_a0, call_a1, (s16)(call_a2 + 2))) {
        temp_a0 = ((*(s16 *)(&D_8006CCD8 + (((S_81814C48_1 *)arg0)->unk_14 * 2)) *
                    ((S_81814C48_1 *)arg0)->unk_32) << 9) +
                  (rand() & 0xFFFF);
        accum = ((S_81814C48_0 *)arg1)->unk_00.at00.v + temp_a0;
        ((S_81814C48_0 *)arg1)->unk_00.at00.v = accum;
        temp_a0_2 = ((*(s16 *)(&D_8006CCE8 + (((S_81814C48_1 *)arg0)->unk_14 * 2)) *
                      ((S_81814C48_1 *)arg0)->unk_32) << 9) +
                    (rand(temp_a0) & 0xFFFF);
        accum = ((S_81814C48_0 *)arg1)->unk_04.at00.v + temp_a0_2;
        ((S_81814C48_0 *)arg1)->unk_04.at00.v = accum;
        random = rand(temp_a0_2);
        tail_offset = 0xFFFE0000;
        accum = ((S_81814C48_0 *)arg1)->unk_08.at00.v + tail_offset;
        accum -= random & 0xFFF;
        ((S_81814C48_0 *)arg1)->unk_08.at00.v = accum;
    }
    temp_v0 = (u16)((S_81814C48_1 *)arg0)->unk_32 - 8;
    ((S_81814C48_1 *)arg0)->unk_32 = temp_v0;
    if (((temp_v0 << 16) <= 0) || (((S_81814C48_2 *)arg2)->unk_14 & 0x8000)) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Guarded a0/a1/a2 call-argument pins fence D_80025338 without
   growing the retail 0x20 s1/s0/s2 frame. Byte table bases with s16 loads
   plus explicit accumulator RMWs place each lw before mflo. A tail a0
   constant pin and direct D_800814A0 scalar RMW remove the two cascades. */
