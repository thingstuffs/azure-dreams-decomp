#include "common.h"

extern void func_80018614(s32, s32, s32);
extern void func_80018674(void);

void func_800186AC(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0x1E) {
        func_80018674();
        return;
    }
    func_80018614(arg0, arg1, 0x1E);
}
