#include "common.h"

typedef struct Struct_80083460 {
    u8 pad[10];
    u16 count;
} Struct_80083460;

extern u8 *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80012090;
extern s16 D_8008146C;
extern Struct_80083460 D_80083460[];
extern u8 D_800C0180[];
extern u8 D_800DF45C[];
extern u8 D_800E1375[];
extern u8 D_800E13B7[];

extern s32 func_80033BC0(s32);
extern void func_8008D344(void *, void *, void *, s32);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern s32 func_800AD6FC(void *, u16, s32);
extern s32 func_800BBA40(u8, u8, s16, void *, s32, s32, void *);

s32 func_800C0230(u8 *arg0, s32 arg1, s16 arg2, s32 arg3) {
    u8 *temp_v0;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if ((void *)arg0 == D_800E3D7C) {
        *(s32 *)(arg0 + 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, 0);
        return 0;
    }
    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1);
        if (func_800AD6FC(arg0, D_800DDE84[arg0[0x13]] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        D_80083460->count--;
        goto block_update;
    }
    ASM_SCHED_BARRIER();
    if (D_80012090 == 0 && D_8008146C == 0x28 && func_80033BC0(0xA2) == 0) {
        func_800997FC(D_800E1375);
        D_80083460->count--;
        func_80098B38(arg1);
        return 1;
    }
    temp_v0 = *(u8 **)(arg0 - 0x14);
    if (func_800BBA40(temp_v0[0x24], temp_v0[0x25],
                      *(s16 *)(arg0 + 0x88), D_800DF45C,
                      0x2800, 0x208020, D_800C0180) == 0) {
        return 0;
    }
    func_800997FC(D_800E13B7);
    D_80083460->count++;

block_update:
    func_80098B38(arg1);
    return 1;
}
