#include "common.h"

extern void func_80016CC4(void);
extern s32 func_8001A554(s32 arg0);
extern s32 func_8001A64C(s32 arg0);
extern s32 func_8001A8EC(s32 arg0);
extern u8 D_80016000[0x10];

s32 func_80017D94(void) {
    s32 arg0;

    func_80016CC4();
    if (func_8001A8EC(6) != 0) {
        func_8001A554(0x93A);
    }
    if (func_8001A8EC(0xB) != 0) {
        func_8001A554(0x93B);
    }
    if (func_8001A64C(0x93A) == 0) {
        goto check_93b;
    }
    if (func_8001A64C(0x94A) != 0) {
        arg0 = 0x93C;
        goto join;
    }

check_93b:
    if (func_8001A64C(0x93B) == 0) {
        goto callback;
    }
    if (func_8001A64C(0x948) == 0) {
        goto callback;
    }
    func_8001A554(0x93C);
    func_8001A554(0x946);
    arg0 = 0x947;

join:
    func_8001A554(arg0);
    return 1;

callback:
    {
        s8 *p1 = *(s8 **)D_80016000;
        s8 *p2 = *(s8 **)(p1 + 0x20);
        s32 (*fn)(s32, s32) = *(s32 (**)(s32, s32))(p2 + 0x2F8);
        fn(0xF, 0x200);
    }
    return 0;
}
