/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"


typedef struct S_800AF674_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    s32 * unk_20;
} S_800AF674_2;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_00 in func_800AF674 */


typedef struct S_800AF674_0 {
    u8 pad_00[0xA8];
    union { s32 s; s32 * u; } unk_A8;   /* accessed as both */
} S_800AF674_0;   /* arg0 in func_800AF674 */


s32 func_8004AC3C();
s32 func_8004DC14();
M2C_UNK func_800B0318();

/* Initialize the output and fill up to ten slots with converted entries from the current page. */
void func_800AF674(S_800AF674_0 *state) {
    s32 conversion_aux;
    s32 *output_slot;
    s32 entry_value;
    s32 converted_value;
    s32 entry_index;
    s32 slot_index;

    slot_index = 0x10;
    func_800B0318(state->unk_A8.s);
    entry_index = ((S_800AF674_2 *)(((Rec_func_800AF254_arg1 *)state)->unk_00))->unk_10 * 0xA;
next_entry:
    if (entry_index < ((S_800AF674_2 *)(((Rec_func_800AF254_arg1 *)state)->unk_00))->unk_1C) {
        entry_value = ((S_800AF674_2 *)(((Rec_func_800AF254_arg1 *)state)->unk_00))->unk_20[entry_index];
        converted_value = func_8004AC3C(entry_value, &conversion_aux);
        entry_index += 1;
        converted_value = func_8004DC14(converted_value, conversion_aux);
        output_slot = state->unk_A8.u[slot_index];
        slot_index += 1;
        *output_slot = converted_value;
        if (slot_index < 0x1A) {
            goto next_entry;
        }
    }
}
