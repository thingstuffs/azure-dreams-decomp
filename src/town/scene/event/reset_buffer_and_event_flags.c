#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s8 D_80018AF8[];
extern u16 D_80019114;
extern s8 *D_80019118;

extern void func_80018548(s32);
extern void func_800185C0(s32);
extern s32 func_80018640(s32);

/* Resets the town buffer and updates callback-dependent and default flags. */
void reset_buffer_and_event_flags(void) {
    D_80019118 = D_80018AF8;
    D_80019114 = 0;

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(F_sbs35_pad01);
    } else {
        func_80018548(F_sbs35_pad01);
    }

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(F_sbs35_pad02);
    } else {
        func_80018548(F_sbs35_pad02);
    }

    if ((func_80018640(F_sbs35_pad01) != 0) &&
        (func_80018640(F_sbs35_pad02) != 0)) {
        func_80018548(F_sbs35_pad03);
    } else {
        func_800185C0(F_sbs35_pad03);
    }

    func_800185C0(F_sbs35_pad12);
    func_800185C0(F_sbs35_pad13);
    func_800185C0(F_sbs35_pad14);
    func_800185C0(F_sbs35_pad15);
    func_80018548(F_sbs35_pad16);
}
