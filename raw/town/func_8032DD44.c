#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80019A34(s32, s32);
extern void func_80019BC0(void);
extern void func_80019DFC(void *, void *, s32, s32);
extern void func_8001ACE8(s32);
extern s32 func_8001ADE0(s32);
extern void *D_80016000;
extern M2C_UNK D_8001BE2C;
extern M2C_UNK D_8001BE44;
extern M2C_UNK D_8001C354;

void func_80018544(s32 arg0, s32 unused, s32 arg2) {
    void *arg;

    if ((arg2 == 0x1E) && (func_80019A34(0xD, 1) != 0)) {
        M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x78)(0);
        func_8001ACE8(0x1460);
        func_80019BC0();
    }

    if (func_8001ADE0(0x1460) != 0) {
        arg = &D_8001BE2C;
    } else {
        arg = &D_8001BE44;
    }
    func_80019DFC(arg, &D_8001C354, arg0, arg2);
}
