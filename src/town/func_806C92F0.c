#include "common.h"

extern s32 func_800175BC(s32);
extern void func_80016A78(void);
extern void func_80016B20(s32, s32);

/* If flag 0x3EC is set, call func_80016A78 first; then func_80016B20(target, value). */
void func_800162F0(s32 target, s32 value) {
    if (func_800175BC(0x3EC) != 0) {
        func_80016A78();
    }
    func_80016B20(target, value);
}
