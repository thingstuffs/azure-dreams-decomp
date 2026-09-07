#include "common.h"

extern s32 func_800169B8(void) __attribute__((noreturn));
extern s32 func_80019928(void);
extern void func_8001A418(s32);
extern void func_8001A490(s32);

s32 func_80016980(void) {
    s32 result;

    result = func_80019928();
    if (result == 0) {
        register s32 ret ASM_REG("$2");

        func_8001A418(0x7A0);
        ASM_KEEP(result);
        ret = result;
        ASM_TAILSLOT_PIN(ret);
        func_800169B8();
        return result;
    }
    func_8001A490(0x7A0);
    return result;
}
