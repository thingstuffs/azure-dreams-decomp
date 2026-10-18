#include "common.h"
#include "m2c_compat.h"
void func_80047358(s32, void *, s32);            /* extern */
extern M2C_UNK D_80408D74;

/* Processes the context using the four-entry table at D_80408D74. */
void func_80020AEC(s32 context) {
    func_80047358(context, &D_80408D74, 4);
}
