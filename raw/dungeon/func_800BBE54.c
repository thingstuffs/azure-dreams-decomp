#include "common.h"

extern void *D_800E3D7C[];
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_80083460[];
extern u8 D_800C152C[];
extern u8 D_800DF514[];
extern u8 D_800E14A6[];

s32 func_80098864(s32, s32);
void func_8008D344(void *, void *, void *, s32);
void func_800A6480(void *, s32);
s32 func_800AD6FC(void *, s32, s32);
void func_800A5F38(void *, s32);
s32 func_800BBA40(u32, u32, s32, void *, s32, s32, void *);
void func_800997FC(void *);
void func_80098B38(s32);

s32 func_800C15B4(void *arg0, s32 arg1, s16 arg2, s32 arg3) {
    void *temp_v0;
    u8 *ptr;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if (arg0 == D_800E3D7C[0]) {
        *(s32 *)((u8 *)arg0 + 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, 0);
        return 0;
    }
    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, arg1);
        if (func_800AD6FC(arg0, D_800DDE84[*(u8 *)((u8 *)arg0 + 0x13)] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        ptr = D_80083460;
        *(u16 *)(ptr + 10) = *(u16 *)(ptr + 10) - 1;
        goto block_11;
    }
    temp_v0 = *(void **)((u8 *)arg0 - 0x14);
    if (func_800BBA40(*(u8 *)((u8 *)temp_v0 + 0x24), *(u8 *)((u8 *)temp_v0 + 0x25), *(s16 *)((u8 *)arg0 + 0x88), &D_800DF514, 0x2800, 0x802020, &D_800C152C) == 0) {
        return 0;
    }
    func_800997FC(&D_800E14A6);
block_11:
    func_80098B38(arg1);
    return 1;
}
