#include "common.h"

extern u8 D_80081471;
extern u8 D_80081485;
extern s32 D_800E3D7C[];
extern u8 D_800E04BA[];
extern u8 D_800E04E6[];

extern void func_800997FC(void *arg0);
extern void func_80099844(s32 arg0, void *arg1);
extern void func_800C77D0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s16 func_80098C80(s32 arg0);
extern void func_8009F644(void *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_8008D388(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    if ((D_80081485 != 0) || (D_80081471 != 0)) {
        if (D_80081471 != 0) {
            func_800997FC(D_800E04BA);
            return 0;
            __asm__ __volatile__("" ::: "memory");
            return 0;
        }
        func_80099844(D_800E3D7C[0], D_800E04E6);
        return 0;
    }
    *(s32 *)((u8 *)arg3 + 0x1C) |= 0x100000;
    *(s32 *)((u8 *)arg0 + 0x124) = 0;
    *(s8 *)((u8 *)arg0 + 0x9A) = 0x22;
    *(s8 *)((u8 *)arg0 + 0x9B) = 0;
    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
    func_800C77D0((u8 *)arg0 - 0x20, arg1, 8, 0x300);
    func_8009F644(arg3, 0x48, func_80098C80(*(s32 *)((u8 *)arg0 + 0xBC)), 0);
    return 1;
}
