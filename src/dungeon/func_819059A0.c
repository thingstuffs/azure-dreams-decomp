#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800251A0_0_pre {
    u16 unk_00;
} S_800251A0_0_pre;   /* the 0x2 bytes before arg0 in func_800251A0, addressed as arg0[-1] */

typedef struct S_800251A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800251A0_0;   /* arg0 in func_800251A0 */


typedef struct DungeonAnimSlot {
    u8 pad_00[0x50];
    s16 field_50;
    u8 pad_52[0x10];
    u16 field_62;
} DungeonAnimSlot;

extern s32 func_800644B8(s32);
extern s16 D_800267B8[5];

/* Update eight animation slots and mark completion when the countdown expires. */
void func_800251A0(void *anim_state)
{
    s16 next_phase;
    s32 slot_index;
    u16 ticks_left;
    u16 phase;
    s32 offset;
    s32 offset_delta;
    DungeonAnimSlot *setup_slot;
    DungeonAnimSlot *slot;

    ticks_left = ((S_800251A0_0 *)anim_state)->unk_02;
    D_800267B8[0] = 1;
    ((S_800251A0_0 *)anim_state)->unk_02 = ticks_left - 1;
    for (slot_index = 1, setup_slot = (DungeonAnimSlot *)((u8 *)anim_state + 2); slot_index < 9; slot_index++) {
        setup_slot->field_62 = slot_index * 0x10;
        setup_slot = (DungeonAnimSlot *)((u8 *)setup_slot + 2);
    }

    slot_index = 1;
    while (slot_index < 9) {
        slot = (DungeonAnimSlot *)((u8 *)anim_state + slot_index * 2);
        offset_delta = func_800644B8(slot->field_50) >> 9;
        offset = slot->field_62;
        phase = (u16)slot->field_50;
        offset += offset_delta;
        next_phase = phase + 0x50;
        slot->field_50 = next_phase;
        slot->field_62 = offset;
        if (next_phase >= 0x1001) {
            s16 wrapped_phase;

            wrapped_phase = phase - 0xFB0;
            slot->field_50 = wrapped_phase;
        }
        slot_index += 1;
    }


    if ((s16)((S_800251A0_0 *)anim_state)->unk_02 <= 0) {
        ((S_800251A0_0_pre *)anim_state)[-1].unk_00 =
            (u16)(((S_800251A0_0_pre *)anim_state)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
