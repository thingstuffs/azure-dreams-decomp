#include "common.h"

extern s8 D_80016000[];
extern s32 D_80018FEC;
extern s32 *D_800190D8;
extern s32 D_80019A74;

extern s32 func_80018C74();
extern s32 func_80018CEC();
extern s32 func_80018D6C();

void func_80016FB4(void) {
    D_800190D8 = &D_80018FEC;
    func_80018C74(0xFDE);
    func_80018CEC(0xFDF);

    if (func_80018D6C(0xFDA) == 0) {
        func_80018CEC(0xFDE);
        func_80018C74(0xFDF);
        *(s32 **)(*(s8 **)(*(s8 **)D_80016000 + 0x1C) + 0x40) = &D_80019A74;
    }

    if (func_80018D6C(0x11FD) != 0) {
        func_80018CEC(0xFE6);
        return;
    }

    func_80018C74(0xFE6);
}
