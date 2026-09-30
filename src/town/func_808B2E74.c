#include "common.h"

typedef struct S_808B2E74_0 {
    u8 pad_00[0xF40];
    u8 *unk_F40;
} S_808B2E74_0;   /* the state block at its constant address */

extern u8 D_A0700000[];

/* Clears bitmap bits for three pairs of stored IDs. */
void func_808B2E74(void)
{
    s32 slot;
    s32 slot_offset;

    for (slot = 1; slot < 4; slot++) {
        s32 first_id;
        s32 second_id;

        slot_offset = slot;
        slot_offset <<= 1;
        first_id = *(s16 *)(D_A0700000 + 0xF24 + slot * 2);
        ((S_808B2E74_0 *)0xA0700000)->unk_F40[first_id / 32] &= ~(1 << (first_id % 32));
        second_id = *(s16 *)(D_A0700000 + 0xF1C + slot_offset);
        ((S_808B2E74_0 *)0xA0700000)->unk_F40[second_id / 32] &= ~(1 << (second_id % 32));
    }
}
