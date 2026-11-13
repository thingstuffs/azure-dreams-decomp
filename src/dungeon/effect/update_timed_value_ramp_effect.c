#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect.h"

typedef struct S_800251F0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x10];
    u16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x62];
    u16 unk_8C;
} S_800251F0_0;   /* arg1 in update_timed_value_ramp_effect */

typedef struct S_800251F0_1 {
    u8 pad_00[0x6428];
    s16 unk_6428;
} S_800251F0_1;   /* page in update_timed_value_ramp_effect */


extern u8 D_80020000[];

/*
 * Counts down the effect lifetime, advances an eight-step byte pattern, and grows a value trail up
 * to 32 entries. Increases trail values by two each update and flags removal when the timer
 * reaches zero.
 */
void update_timed_value_ramp_effect(void *object_ptr)
{
    S_800251F0_0 *object_bytes;
    u16 remaining_ticks;
    s32 value_index;

    object_bytes = object_ptr;
    remaining_ticks = object_bytes->unk_02;
    ((S_800251F0_1 *)D_80020000)->unk_6428 = 1;
    object_bytes->unk_02 = remaining_ticks - 1;
    object_bytes->unk_8C += 200;
    object_bytes->unk_0A++;
    if ((s16)object_bytes->unk_0A >= 2) {
        object_bytes->unk_0A = 0;
        object_bytes->unk_0C = (u16)(object_bytes->unk_0C + 1);
    }
    if (object_bytes->unk_0C >= 33) {
        object_bytes->unk_0C = 32;
    }

    value_index = 0;
    while (value_index < object_bytes->unk_0C) {
        u8 *value_base;

        value_base = (u8 *)object_bytes + value_index;
        value_base[0x50] += 2;
        value_index++;
    }

    {
        s32 state;

        state = *(s16 *)((u8 *)object_bytes + 0x1E);
        switch (state) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            object_bytes->unk_1E++;
            object_bytes->unk_28 += 0x10;
            break;
        case 3:
            object_bytes->unk_1E++;
            object_bytes->unk_28 -= 0x30;
            object_bytes->unk_29 += 0x20;
            break;
        case 7:
            object_bytes->unk_28 -= 0x30;
            object_bytes->unk_29 -= 0x20;
            object_bytes->unk_1E = 0;
            break;
        }
    }

    if ((s16)object_bytes->unk_02 <= 0) {
        (*(u16 *)((u8 *)object_bytes + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
