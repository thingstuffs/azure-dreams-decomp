/* G00740: Initialize the global interface and select its byte entry.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_594800_80016000:80018FB4.
 * Only the strong PD gap is included; complete file edges remain unknown.
 */
#include "town/scene/interface_setup_g00740.h"

/* Calls func_800181C8 with the selected 24-byte entry and two forwarded values. */
void call_24_byte_entry_two(s32 firstValue, s32 unusedValue, s32 secondValue) {
    s32 entryIndex;
    s32 twiceEntryIndex;
    s32 thriceEntryIndex;
    thriceEntryIndex = D_80018FB4;
    entryIndex = thriceEntryIndex - (thriceEntryIndex / 3) * 3;
    twiceEntryIndex = entryIndex << 1;
    thriceEntryIndex = entryIndex + twiceEntryIndex;

    func_800181C8(
        (thriceEntryIndex << 3) + (u8 *)&D_80018FB8,
        &D_8001925C,
        firstValue,
        secondValue);
}

/* Runs the global interface setup sequence and saves its initial result. */
s32 run_global_interface_setup_sequence(void) {
    D_80018FB4 = ((S_func_80016D74_2 *)
        ((S_func_80016D74_1 *)
         ((S_func_80016D74_0 *)((s8 *)(&D_80016000)))->unk_00)->unk_20)->unk_54(3);
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    ((S_func_80016D74_2 *)
        ((S_func_80016D74_1 *)
         ((S_func_80016D74_0 *)((s8 *)(&D_80016000)))->unk_00)->unk_20)->unk_2F8(0x10, 0x200);
    return 0;
}
