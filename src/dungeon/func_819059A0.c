#include "modules/dungeon_ovl_1924800.h"

   /* the 0x2 bytes before arg0 in update_effect_animation_slots, addressed as arg0[-1] */

   /* arg0 in update_effect_animation_slots */

/* Update eight animation slots and mark completion when the countdown expires. */
void update_effect_animation_slots(void *anim_state)
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
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
