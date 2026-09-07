#include "common.h"

typedef s32 M2C_UNK;

extern void func_80033CD8();
extern void func_80045340();
extern M2C_UNK D_800A833C;
extern s32 D_800D0E44;
extern M2C_UNK D_800F8A70;

void func_800A82F0(void *arg0, M2C_UNK arg1, void *arg2) {
    void *sp0;

    *(M2C_UNK **) ((s8 *) arg0 - 0x10) = &D_800A833C;
    D_800D0E44 = 0x14;
    sp0 = &D_800F8A70;
    *(void **) ((s8 *) arg2 + 8) = (void *) ((s8 *) sp0 + 0xF0);
    func_80033CD8(arg0, func_80045340);
}
