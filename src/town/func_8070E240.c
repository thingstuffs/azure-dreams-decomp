#include "common.h"

extern void func_80016CC4(void);
extern void func_80016DBC(void);
extern s32 func_8001991C(s32, s32);
extern void func_80019988(void);
extern void func_8001A5CC(s32);
extern s32 func_8001A64C(s32);
extern u8 D_80016000[0x10];

typedef void (*Callback)(s32, s32);

s32 func_80017240(s32 arg0, s32 arg1) {
    func_80016CC4();
    func_80016DBC();

    if (func_8001A64C(0x943) != 0) {
        func_80019988();
        if (func_8001991C(arg0, arg1) != 0) {
            func_8001A5CC(0x943);
            return 1;
        }
    }

    (*(Callback *)((u8 *)((void **)*(void **)D_80016000)[8] + 0x2F8))(0xE, 0x200);
    return 0;
}
