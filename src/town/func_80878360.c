#include "common.h"

extern void func_807023A0(void) __attribute__((noreturn));
extern void func_80702670(s32);
extern void func_807026C0(s32);
extern s32 func_80702714(s32);

void func_80702360(void) {
    if ((func_80702714(0x20C) == 0) && (func_80702714(0x268) == 0)) {
        func_80702670(0x24C);
        func_807023A0();
        return;
    }
    func_807026C0(0x24C);
}
