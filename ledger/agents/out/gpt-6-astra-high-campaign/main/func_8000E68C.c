#include "common.h"
#include "m2c_compat.h"

extern void *D_80020060[];
M2C_UNK func_80020924();
s32 func_80021594();
s32 func_8002190C();
extern M2C_UNK D_80028530[];
extern M2C_UNK D_80028538[];
extern M2C_UNK D_80028538_read[] __asm__("D_80028538");
extern M2C_UNK D_80028538_write[] __asm__("D_80028538");
extern M2C_UNK D_800287D0[];
extern M2C_UNK D_80084118[];

/* Track consecutive state samples for a slot and apply state updates. */
s32 func_8002168C(void) {
    static void *const state_labels[] = { &&state_1, &&state_2, &&state_3, &&state_4, &&state_5, &&store_state };
    s32 slot;
    s32 state;
    s32 count_offset;
    s32 slot_offset;
    s32 *repeat_counts;

    state = func_80021594();
    slot = func_8002190C();
    if (state == 0) {
        goto done;
    }
    if (*(s32 *)((s8 *)&D_80028538_read + slot * 4) != state) {
        goto reset_count;
    }
    *(s32 *)((s8 *)&D_80028530 + slot * 4) += 1;
    slot_offset = slot * 4;
    goto store_state;
reset_count:
    *(s32 *)((s8 *)&D_80028530 + slot * 4) = 0;
    slot_offset = slot * 4;
store_state:
    *(s32 *)((s8 *)&D_80028538_write + slot * 4) = state;
    if ((u32) (state - 1) >= 5U) {
        goto update_slot;
    }
    (void)state_labels;
    goto *D_80020060[(u32)(state - 1)];
state_1:
state_2:
    D_800287D0[slot] = state;
    goto update_slot;
state_3:
    repeat_counts = D_80028530;
    count_offset = slot * 4;
    goto check_count;
state_4:
state_5:
    D_80084118[slot] = 0;
    count_offset = slot * 4;
    repeat_counts = D_80028530;
check_count:
    if (*(s32 *)(count_offset + (s32)repeat_counts) < 0xB) {
        func_80020924(slot, (s32 *)(count_offset + (s32)repeat_counts));
        goto done;
    }
    *(s32 *)((s8 *)&D_800287D0 + count_offset) = state;
    *(s32 *)(count_offset + (s32)repeat_counts) = 0;
    *(s32 *)((s8 *)&D_80028538 + count_offset) = 0;
    func_80020924(slot, (s32 *)(count_offset + (s32)repeat_counts));
    goto done;
update_slot:
    func_80020924(slot, (s32 *)slot_offset);
done:
    return state;
}
