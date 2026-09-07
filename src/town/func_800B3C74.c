#include "common.h"

extern void func_800B1390(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_800B0944(void *, void *, void *);
extern void func_800B1188(void *);

void func_800B13D4(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_800B1390(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    func_800B0944((u8 *)arg0 + 0xBC, (u8 *)arg0 + 0x94,
                  (u8 *)arg0 + 0xA4);
    func_800B1188(arg0);
}
