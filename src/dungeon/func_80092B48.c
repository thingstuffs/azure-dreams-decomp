#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Item;

typedef struct {
    u8 pad0[0x1C];
    s32 flags;
    u8 pad20[0x2C];
    Item *field4C;
    u8 pad50[0x34];
    u8 b84;
    u8 b85;
} Arg0;

extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern s32 *D_800E3D18[];
extern Item *func_80097F84(Item *, u8 *, u8 *, s32);
/* Retail sets a3 to 10 at 0x80099114 before reading it; no incoming argument. */
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099368(Item *, s32);
extern s32 func_80099734(Arg0 *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800483AC(s32);
extern void func_80048568(s32);
extern void func_80048590(s32);
extern u8 D_80088B64[];
extern u8 D_800DD2B4[];
extern u8 D_800DD2C4[];
extern u8 D_800DD2D4[];
extern u8 D_800DD2E0[];
extern u8 D_800E080A[];
extern u8 D_800E081C[];
extern u8 D_800E0844[];
extern u8 D_800E0853[];
extern u8 D_800E0862[];
extern u8 D_800E3CF8[];
extern u8 D_800E3D80[];
extern u8 D_800DD2C4_index[] __asm__("D_800DD2C4");
extern u8 D_800DD2B4_index[] __asm__("D_800DD2B4");

void func_800982A8(Arg0 *arg0, Item *arg1) {
    s32 temp_v0;
    register s32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s2;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 tail_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    s32 state;
    s32 item_b3;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    Item *temp_s2;
    Item *var_s0;
    u8 *head_c;
    u8 *head_b;
    u8 head_b_value;

    var_s0 = arg1;
    var_s1 = 0;
    if (var_s0 != NULL) {
        if (var_s0->b1 == 0xF && var_s0->b0 >= 0xD) {
            func_800A56E0(0x506);
            var_s1 = func_800990FC();
               /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            item_b3 = func_80099368(var_s0, func_80099194(D_800E080A, func_80099734(arg0, func_8009929C(8, var_s1))));
            func_80099290(func_80099194(D_80088B64, item_b3));
            func_800A5720(var_s1);
            return;
        }
        var_s0 = func_80097F84(var_s0, D_800E07C0, D_800E07D3, 0);
        if (var_s0 == NULL) {
            return;
        }
    }

    temp_s2 = arg0->field4C;
    if (temp_s2 != NULL) {
        temp_v0 = temp_s2->b3;
        if (temp_v0 & 0x40) {
            func_800A56E0(0x70A);
            var_s1 = func_800990FC();
            item_b3 = func_80099368(temp_s2, func_8009929C(8, var_s1));
            func_80099290(func_80099194(D_800E081C, item_b3));
            func_800A5720(var_s1);
            return;
        }
        temp_s2->b3 = temp_v0 & 0xDF;
        D_800E3D18[0] = (s32 *)D_800E3CF8;
        if (temp_s2 == var_s0) {
            var_s0 = NULL;
        }
        var_s1 = 1;
    }

    if (var_s0 != NULL) {
        item_b3 = var_s0->b3;
        var_s2 = var_s0->b0;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_s0->b3 = item_b3 & 0x7F;
        var_s1 = func_800990FC();
        func_80099290(func_80099194(D_800E0844, func_80099368(var_s0, func_8009929C(8, var_s1))));
        func_800A5720(var_s1);
        D_800E3D18[0] = (s32 *)D_800E3D80;
        tail_index = 0x70A; /* MATCH: prepare a0 in the guard branch delay slot. */
        if (var_s0->b3 & 0x40) {
            arg0->flags |= 0x800;
            func_800A56E0(tail_index);
            var_s1 = func_800990FC();
            func_80099290(func_80099194(D_800E0853, func_80099368(var_s0, var_s1)));
            func_800A5720(var_s1);
        }
        var_s0->b3 |= 0x20;
    } else {
        state = var_s1;
        ASM_KEEP_NV(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (state != 0) {
            var_s1 = func_800990FC();
            temp_v0 = func_8009929C(8, var_s1);
            temp_v0 = func_80099368(arg0->field4C, temp_v0);
            temp_v0 = func_80099194(D_800E0862, temp_v0);
            func_80099290(temp_v0);
            func_800A5720(var_s1);
        }
        head_c = D_800DD2C4;
        arg0->b84 = head_c[0];
        head_b = D_800DD2B4;
        head_b_value = head_b[0];
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        var_s2 = 0;
           /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        arg0->b85 = head_b_value;
           /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    }
    arg0->field4C = var_s0;
    func_800A56E0(0x508);
    tail_index = var_s2;
    if (var_s0->b1 == 0x10) {
        arg0->b84 = D_800DD2E0[tail_index];
        arg0->b85 = D_800DD2D4[tail_index];
        if (tail_index != 0) {
            func_80048590(tail_index);
        } else {
            goto clear_state;
        }
    } else {
        arg0->b84 = D_800DD2C4_index[tail_index];
        arg0->b85 = D_800DD2B4_index[tail_index];
        if (tail_index != 0) {
            func_80048568(tail_index);
        } else {
            goto clear_state;
        }
    }
       /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (var_s2 != 0) {
        return;
    }
clear_state:
    func_800483AC(1);
}
