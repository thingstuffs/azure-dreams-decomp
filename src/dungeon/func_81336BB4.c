#include "common.h"

extern u8 D_80083780[12];
extern u8 *D_800814A8;
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern u8 D_8016A36C[];
extern s16 D_801760D8[];
extern u8 D_801739A0[];
extern void *D_801649B8[];

extern void func_800419EC(s32, s32, void *);
extern void func_80047784(void *, u8, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_801676CC(void *);
extern void func_801690D8(void *, void *, void *, void *);
extern void func_80169C1C(void *, void *, void *);

void func_8016DBB4(u8 *p0, u8 *p1, u8 *p2, u8 *p3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    u8 state;
    s32 mode;
    u8 *base;
    u8 *current;
    void *ptr;
    u16 value;
    u16 next;
    s16 old;
    s32 index;
#define arg0 p0
#define arg1 p1
    u8 *arg2 = p2;
    u8 *arg3 = p3;
    state = arg0[0x9B];
    if (state >= 6U) {
        goto epilogue;
    }
    (void)jt_keep;
    goto *D_801649B8[(u32)state];

jt_c0:
    func_801676CC(arg1);
    *(u16 *)(arg0 + 0x96) = 5;
    arg0[0x9B] = arg0[0x9B] + 1;
    func_800A56E0(0x703);
    D_801760D8[0] = 0;
    goto epilogue;

jt_c1:
    value = *(u16 *)(arg0 + 0x96) - 1;
    *(u16 *)(arg0 + 0x96) = value;
    if ((value << 0x10) <= 0) {
        goto advance;
    }
    if (!( *(u16 *)(arg2 + 0x14) & 0xE000)) {
        goto epilogue;
    }
    goto advance;

jt_c2:
    value = *(u16 *)(arg0 + 0x96) + 1;
    *(u16 *)(arg0 + 0x96) = value;
    if ((s16)value == 1) {
        func_801690D8(arg0, arg1, arg2, D_80083780);
    }
    if (*(s16 *)(arg0 + 0x96) == 2) {
        ptr = D_800814A8;
        *(u16 *)((u8 *)ptr + 0x10C) |= 1;
        *(s16 *)((u8 *)ptr + 0x6A) = *(u16 *)((u8 *)ptr + 0x2A) + 0x800;
        func_800419EC(6, 0xC, ptr);
        func_800A56E0(0x601);
        func_80169C1C(arg0, arg1, arg2);
    }
    if (*(s16 *)(arg0 + 0x96) == 0xB) {
        goto advance;
    }
    goto epilogue;

jt_c3:
    if (!( *(u16 *)(arg2 + 0x14) & 0xE000)) {
        goto epilogue;
    }
    *(s32 *)(arg1 + 0x14) = 0;
    *(s32 *)(arg1 + 0x10) = 0;
    *(s32 *)(arg1 + 0x0C) = 0;
    func_800A2B04(arg1, arg2[0x24], arg2[0x25]);
    mode = arg0[0xAC];
    if (mode == 1) {
        goto set_base1;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto set_base0;
        }
        goto advance;
    }
    if (mode == 2) {
        goto set_base2;
    }
    if (mode == 3) {
        goto set_base3;
    }
    goto advance;

set_base0:
    current = *(u8 **)(arg2 + 0x2C);
    base = D_801739A0;
    goto shared_base;
set_base1:
    current = *(u8 **)(arg2 + 0x2C);
    base = D_801739A0 + 0x8;
    goto shared_base;
set_base2:
    current = *(u8 **)(arg2 + 0x2C);
    base = D_801739A0 + 0x10;
    goto shared_base;
set_base3:
    current = *(u8 **)(arg2 + 0x2C);
    base = D_801739A0 + 0x18;
    goto shared_base;

shared_base:
    if (current != base) {
        *(u8 **)(arg2 + 0x2C) = base;
        index = ((s32)(D_80083228[0] + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, *(u8 *)((u32)index + (u32)base), 0);
    }
    goto advance;

jt_c4:
    old = *(u16 *)(arg0 + 0x96);
    next = old + 1;
    *(u16 *)(arg0 + 0x96) = next;
    if (old < 0x50) {
        goto epilogue;
    }
    goto advance;

advance:
    state = arg0[0x9B];
    *(u16 *)(arg0 + 0x96) = 0;
    arg0[0x9B] = state + 1;
    goto epilogue;

jt_c5:
    arg3[0x73] = 0;
    arg3[0x72] = 0;
    *(u8 **)(arg0 + 0x8C) = D_8016A36C;
    D_8008346C[0] = 0;
    *(u16 *)(arg3 + 0x46) &= 0x7FFF;

epilogue:
    return;
}
