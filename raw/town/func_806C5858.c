#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s8 D_80016000[];
extern s8 D_8001ABF9;

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

s32 func_80016858(void) {
    if ((func_80018D6C(0x7D1) != 0) &&
        (func_80018D6C(0x7D2) == 0) &&
        (func_80018D6C(0xFDC) != 0)) {
        func_80018C74(0x7D9);
        FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C), void *, 0x40) = &D_8001ABF9;
        return 1;
    }
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
