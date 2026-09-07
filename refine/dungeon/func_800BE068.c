#include "common.h"

extern void *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_800E2082[];
extern u16 D_80083460[];

extern s32 func_8008D330(void *, u8 *, u8 *, void *);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800A5F38(void *, s32);
extern void func_800A56E0(u32);
extern void func_80041E70(void *);
extern void func_80099844(void *, u8 *);
extern void func_80098B38(s32);

/* Applies a stat-reducing item to a target and handles item consumption. */
s32 func_800C37C8(void *target, s32 item, s16 use_type) {
    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = item;
        func_8008D330(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A63B8(target, item, use_type);
        if (func_800AD6FC(target, (D_800DDE84[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    }

    if (*((u8 *)target + 0x27) >= 2) {
        func_800A56E0(0x615);
        (*((u8 *)target + 0x27))--;
        func_80041E70(target);
        if (*(s32 *)((u8 *)target + 0x14) & 0x4000) {
            func_80099844(target, D_800E2082);
        }
    }

    func_80098B38(item);
    D_80083460[5]--;
    return 1;
}
