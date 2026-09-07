#include "common.h"

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
extern s16 D_800267B8;
extern s32 D_800814A0[3];

/* Update eight animation slots and mark completion when the countdown expires. */
void func_800251A0(void *anim_state)
{
    s16 next_phase;
    s32 slot_index;
    register s32 active_value ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 ticks_left ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s16 *active_flag;
    u16 phase;
    register u16 offset ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 offset_delta;
    DungeonAnimSlot *setup_slot;
    register DungeonAnimSlot *slot ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */

    slot_index = 1;
    setup_slot = (DungeonAnimSlot *)((u8 *)anim_state + 2);
    ticks_left = ((S_800251A0_0 *)anim_state)->unk_02;
    active_flag = &D_800267B8;
    ASM_KEEP(ticks_left);   /* MATCH pin: retail schedule: same instructions, different order without it */
    active_value = slot_index;
    *active_flag = (s16)active_value;
    ASM_KEEP(active_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_800251A0_0 *)anim_state)->unk_02 = (u16)(ticks_left - 1);
    do {
        setup_slot->field_62 = (s16)(slot_index * 0x10);
        slot_index += 1;
        setup_slot = (DungeonAnimSlot *)((u8 *)setup_slot + 2);
    } while (slot_index < 9);

    slot_index = 1;
    slot = (DungeonAnimSlot *)((u8 *)anim_state + 2);
    do {
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
        slot = (DungeonAnimSlot *)((u8 *)slot + 2);
    } while (slot_index < 9);


    if ((s16)((S_800251A0_0 *)anim_state)->unk_02 <= 0) {
        ((S_800251A0_0_pre *)anim_state)[-1].unk_00 =
            (u16)(((S_800251A0_0_pre *)anim_state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
