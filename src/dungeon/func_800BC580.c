#include "common.h"

extern u8 *D_800E3D7C[];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80083460[3];
extern u8 D_800E1532[];

extern void func_8008D344(void *, u8 *, u8 *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, u16, s32);
extern void func_800C1F28(s32, s16);
extern s32 func_8003FA44(s32);

s32 func_800C1CE0(void *arg0, s32 arg1, s16 arg2, s32 arg3) {
    s32 i;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_a0;
    u8 *global_page;
    u8 *counter_page;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }

    global_page = (u8 *)0x800E0000;
    if (arg0 == *(u8 **)(global_page + 0x3D7C)) {
        *(s32 *)((u8 *)arg0 + 0x110) = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[((u8 *)arg0)[0x13]] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        temp_s2 = func_800990FC();
        temp_s1 = temp_s2;
        if ((*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC) != 0) ||
            (*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xB0) != 0)) {
            if (func_8003FA44(4) == 0) {
                return 0;
            }
            i = 0;
        loop_start:
                temp_a0 = *(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC + i * 4);
                if (temp_a0 != 0) {
                    func_800C1F28(temp_a0, (s16)i);
                }
                i += 1;
            if (i < 2) {
                goto loop_start;
            }
            temp_s1 = func_80099194(D_800E1532, temp_s1);
            func_800A56E0(0x501);
        } else {
            temp_s1 = func_80099194(D_800E1532 + 0x17, temp_s2);
        }
        func_80099290(temp_s1);
        func_800A5720(temp_s2);
    }

    counter_page = (u8 *)D_80083460;
    (*(u16 *)(counter_page + 0xA))--;
    func_80098B38(arg1);
    return 1;
}
