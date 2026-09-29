#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800251F0_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    u16 unk_0A;
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    u8 pad_0E[0x10];
    u16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x62];
    u16 unk_8C;
} S_800251F0_0;   /* arg1 in func_800251F0 */

typedef struct S_800251F0_1 {
    u8 pad_00[0x6428];
    s16 unk_6428;
} S_800251F0_1;   /* page in func_800251F0 */


extern u8 D_80020000[];

/* Advance object counters and animation values, and flag expiration. */
void func_800251F0(void *object_ptr)
{
    u8 *object_bytes;
    u16 remaining_ticks;
    s32 value_index;

    object_bytes = object_ptr;
    remaining_ticks = ((S_800251F0_0 *)object_bytes)->unk_02.s;
    ((S_800251F0_1 *)D_80020000)->unk_6428 = 1;
    ((S_800251F0_0 *)object_bytes)->unk_02.s = remaining_ticks - 1;
    ((S_800251F0_0 *)object_bytes)->unk_8C += 200;
    ((S_800251F0_0 *)object_bytes)->unk_0A++;
    if ((s16)((S_800251F0_0 *)object_bytes)->unk_0A >= 2) {
        ((S_800251F0_0 *)object_bytes)->unk_0A = 0;
        ((S_800251F0_0 *)object_bytes)->unk_0C.s++;
    }
    if (((S_800251F0_0 *)object_bytes)->unk_0C.u >= 33) {
        ((S_800251F0_0 *)object_bytes)->unk_0C.u = 32;
    }

    value_index = 0;
    while (value_index < ((S_800251F0_0 *)object_bytes)->unk_0C.u) {
        u8 *value_base;

        value_base = object_bytes + value_index;
        value_base[0x50] += 2;
        value_index++;
    }

    {
        s32 state;

        state = *(s16 *)(object_bytes + 0x1E);
        switch (state) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            ((S_800251F0_0 *)object_bytes)->unk_1E++;
            ((S_800251F0_0 *)object_bytes)->unk_28 += 0x10;
            break;
        case 3:
            ((S_800251F0_0 *)object_bytes)->unk_1E++;
            ((S_800251F0_0 *)object_bytes)->unk_28 -= 0x30;
            ((S_800251F0_0 *)object_bytes)->unk_29 += 0x20;
            break;
        case 7:
            ((S_800251F0_0 *)object_bytes)->unk_28 -= 0x30;
            ((S_800251F0_0 *)object_bytes)->unk_29 -= 0x20;
            ((S_800251F0_0 *)object_bytes)->unk_1E = 0;
            break;
        }
    }

    if (((S_800251F0_0 *)object_bytes)->unk_02.u <= 0) {
        (*(u16 *)((u8 *)object_bytes + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
