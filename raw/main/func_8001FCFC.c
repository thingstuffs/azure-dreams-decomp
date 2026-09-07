#include "common.h"

extern s32 func_80402268(void);
extern s32 func_80402290(void);
extern void func_80406C74(void *arg0);
extern void func_80406CB8(void *arg0);
extern void func_80406D8C(void) __attribute__((noreturn));
extern void func_80406C2C(void);
extern void func_80406B9C(void);
extern u8 D_8009DDD8[];

void func_8001FCFC(void *arg0) {
    s32 idx;

    idx = *(s32 *)((u8 *)arg0 + 0x2C);
    if (*(s32 *)(D_8009DDD8 + (idx << 7)) != 0) {
        *(void (**)(void))((u8 *)arg0 - 0x10) = func_80406C2C;
        func_80406D8C();
    }
    if (func_80402268() >= 3) {
        *(void (**)(void))((u8 *)arg0 - 0x10) = func_80406B9C;
        func_80406D8C();
    }
    if (func_80402290() != 0) {
        func_80406C74(arg0);
        func_80406D8C();
    }
    func_80406CB8(arg0);
}
