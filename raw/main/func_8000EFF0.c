#include "common.h"

extern void func_80021B18(void *arg0, s32 arg1);
extern s32 func_80021B98(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_80021C4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80021EB8(void *arg0);
extern s32 func_80021EE0(void *arg0);

extern s32 D_80083E98[][32];

void func_80021FF0(s32 arg0, void *arg1, s32 arg2) {
    s32 sp18[8];
    s32 *base;
    s32 *entry;
    s32 old_value;

    func_80021B18(sp18, arg0);
    if (func_80021B98(sp18, arg1, 0xC0, 0) == 0) {
        return;
    }
    if (func_80021EE0(arg1) == 0) {
        return;
    }
    if (arg2 != 0) {
        old_value = *(s16 *)((u8 *)arg1 + 0x208);
        *(s16 *)((u8 *)arg1 + 0x208) = 0;
        *(s32 *)((u8 *)arg1 + 0x204) = 0;
        func_80021EB8(arg1);
        base = (s32 *)&D_80083E98;
        entry = (s32 *)((u8 *)base + (arg0 << 7));
        *(s16 *)((u8 *)entry + 8) = 0;
        *(s32 *)((u8 *)entry + 4) = *(s32 *)((u8 *)arg1 + 0x204);
        func_80021C4C(sp18, entry, 1, 4, entry[0]);
        func_80021C4C(sp18, arg1, 1, 0, entry[0]);
        *(s16 *)((u8 *)arg1 + 0x208) = old_value;
        return;
    }
    *(s16 *)((u8 *)arg1 + 0x208) = 0;
}
