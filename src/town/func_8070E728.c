#include "common.h"

typedef s32 (*TownCallback)(s32, s32);

extern void func_80016CC4(void);
extern s32 func_8001A64C(s32);
extern void func_8001A7AC(void);
extern s8 D_80016000[];

s32 func_80017728(void) {
    s32 result;

    func_80016CC4();
    if (func_8001A64C(0x932) == 0) {
        func_8001A7AC();
        (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x2F8))(0xE, 0x200);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
