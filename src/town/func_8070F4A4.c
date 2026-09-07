#include "common.h"

typedef void (*TownCallback)(s32, s32);

extern void func_80016CC4(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s8 D_80016000[];

s32 func_800184A4(void) {
    s32 result;

    func_80016CC4();

    if (func_8001A64C(0x1068) == 0) {
        (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0xE, 0x200);
        result = 0;
        goto done;
    }

    func_8001A554(0x94F);
    func_8001A554(0x93E);
    result = 1;

done:
    return result;
}
