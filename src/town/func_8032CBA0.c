#include "common.h"

extern s32 func_8001ADE0(s16 arg0);
extern void func_80019BC0(void);
extern void func_8001ACE8(s32 arg0);
extern u8 D_8001E6F8[];
extern u8 D_8001F4CD[];
extern u8 D_8001F4E2[];

void *func_800173A0(void *arg0, s32 unused, s32 arg2) {
    if (arg2 == 0x25) {
        if (func_8001ADE0(*(s16 *)((u8 *)arg0 + 0x18)) != 0) {
            return D_8001F4E2;
        }
        func_80019BC0();
        func_8001ACE8(0x145D);
        return D_8001E6F8;
    }
    if (arg2 == 0x44) {
        return D_8001F4CD;
    }
    return 0;
}
