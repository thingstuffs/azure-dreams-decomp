#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
extern void func_8009881C(s32 arg0);
extern void func_80099754(void *arg0);
extern s32 D_80098690;

void func_80098764(void *arg0, void *arg1) {
    u16 temp_v0;
    s32 old4;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        M2C_FIELD(arg1, s32 *, 0) =
            ((func_800644B8(M2C_FIELD(arg0, s16 *, 0x10)) << 9)
             + (M2C_FIELD(arg0, s16 *, 0x30) << 0x10)
             + M2C_FIELD(arg1, s32 *, 0)) / 2;
        M2C_FIELD(arg1, s32 *, 4) =
            ((func_80064584(M2C_FIELD(arg0, s16 *, 0x10)) << 9)
             + (M2C_FIELD(arg0, s16 *, 0x32) << 0x10)
             + (old4 = M2C_FIELD(arg1, s32 *, 4))) / 2;
        func_8009881C(old4);
        return;
    }
    func_80099754(arg1);
    M2C_FIELD(arg0, u16 *, 0xA) = 7;
    M2C_FIELD(arg0, s32 **, 4) = &D_80098690;
}
