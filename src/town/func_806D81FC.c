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
void func_800169FC(void) {
    D_80019118 = D_80018AF8;
    D_80019114 = 0;

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(0x9AC);
    } else {
        func_80018548(0x9AC);
    }

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(0x9AD);
    } else {
        func_80018548(0x9AD);
    }

    if ((func_80018640(0x9AC) != 0) &&
        (func_80018640(0x9AD) != 0)) {
        func_80018548(0x9AE);
    } else {
        func_800185C0(0x9AE);
    }

    func_800185C0(0x9B7);
    func_800185C0(0x9B8);
    func_800185C0(0x9B9);
    func_800185C0(0x9BA);
    func_80018548(0x9BB);
}
