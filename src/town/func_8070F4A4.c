#include "common.h"

typedef void (*TownCallback)(s32, s32);

extern void func_80016CC4(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s8 D_80016000[];

// Dispatches the town callback if check 0x1068 fails, otherwise issues commands 0x94F and 0x93E.
s32 func_800184A4(void) {
    s32 checkPassed;

    func_80016CC4();

    if (func_8001A64C(0x1068) == 0) {
        (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0xE, 0x200);
        checkPassed = 0;
        goto done;
    }

    func_8001A554(0x94F);
    func_8001A554(0x93E);
    checkPassed = 1;

done:
    return checkPassed;
}
