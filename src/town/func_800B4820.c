/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B1DCC_arg0.h"

s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
void func_800B1F10(s32 arg0, s32 arg1);
void func_800B1F48(s32 arg0, s32 arg1, s32 arg2);



typedef struct S_800B1F80_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B1F80_1;   /* temp_s0 in func_800B1F80 */

/* Update the active entry index and notify handlers when its index or ten-entry group changes. */
void func_800B1F80(s8 *state, s32 input) {
    s32 active_slot;
    s32 group_slot;
    s32 index_result;
    s32 next_group;
    s32 next_index;
    S_800B1F80_1 *entry;

    entry = state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_0C * 0x10) + 0x1C);
    index_result = func_80049E1C(entry->unk_08, input, entry->unk_0C);
    next_index = index_result;
    if (next_index >= entry->unk_0C) {
        entry->unk_08 = 0;
        return;
    }
    if (next_index != entry->unk_08) {
        entry->unk_08 = next_index;
        active_slot = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
        next_group = index_result / 10;
        func_800B1F48(*((s32 *)((s8 *)state + (active_slot * 4))), active_slot, next_index);
        if (next_group != entry->unk_00) {
            entry->unk_00 = next_group;
            group_slot = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
            func_800B1F10(*((s32 *)((s8 *)state + (group_slot * 4))), group_slot);
        }
    }
}
