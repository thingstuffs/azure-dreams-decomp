#include "common.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_80095C80();
M2C_UNK func_80095094();
s16 func_80095978();
M2C_UNK func_80094378();
extern void func_80091CC0(void) __attribute__((noreturn));
M2C_UNK func_80095A94();
M2C_UNK func_80094984();
M2C_UNK func_800941D8();

extern u8 D_800CFCEF;
extern M2C_UNK D_800D00E0;
extern M2C_UNK D_800FE488;

void func_80091BD8(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s16 temp_v0_2;

    func_80095C80(arg1);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - M2C_FIELD(arg1, s16 *, 0xA)) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094378(arg0, arg1, arg2);
            func_80091CC0();
        }
        goto block_6;
    }
    if (D_800CFCEF == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (M2C_FIELD(arg0, s16 *, 0xA) == 0) {
        func_80094984(&D_800D00E0, arg0, arg2);
    }
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0xA) - 1;
    M2C_FIELD(arg0, s16 *, 0xA) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        func_800941D8(arg0, arg1, arg2);
    }
}
