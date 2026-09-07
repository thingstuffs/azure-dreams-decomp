#include "common.h"

extern s32 D_804094EC[];
extern s32 D_80408AA0[2];
extern s32 D_80408AA8[];
extern s32 D_80408AB8[];

s32 func_8007BF80();
s32 func_8007BF50();

/* Configures the target using the active state and selected table entry. */
void func_8001ABF4(s32 target, s32 entry_index) {
    s32 *active_value;

    active_value = &D_80408AA0[0];
    if (D_804094EC[0] != 0) {
        active_value = &D_80408AA0[0] + 1;
    }
    func_8007BF80(target, *active_value);
    func_8007BF50(target, &D_80408AA8[0]);
    func_8007BF50(target, D_80408AB8[entry_index]);
}
