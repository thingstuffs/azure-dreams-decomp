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
extern void func_800983C8(void *);
extern void func_80098550(void);
extern void func_800985E4(void);
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
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 var_s2 ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    register s32 tail_index ASM_REG("$4");   /* MATCH pin: retail delay-slot contents depend on it */
    s32 state;
    register s32 item_b3 ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
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
            ASM_USE_NV(var_s1);   /* MATCH pin: retail delay-slot fill depends on it */
            func_80099368(var_s0, func_80099194(D_800E080A, func_80099734(arg0, func_8009929C(8, var_s1))));
            func_800983C8(D_80088B64);
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
            func_80099290(func_80099194(D_800E081C, func_80099368(temp_s2, func_8009929C(8, var_s1))));
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
        ASM_USE_NV(var_s2);   /* MATCH pin: load-bearing for the whole function shape */
        var_s0->b3 = item_b3 & 0x7F;
        var_s1 = func_800990FC();
        func_80099290(func_80099194(D_800E0844, func_80099368(var_s0, func_8009929C(8, var_s1))));
        func_800A5720(var_s1);
        D_800E3D18[0] = (s32 *)D_800E3D80;
        if (var_s0->b3 & 0x40) {
            arg0->flags |= 0x800;
            func_800A56E0(0x70A);
            var_s1 = func_800990FC();
            func_80099290(func_80099194(D_800E0853, func_80099368(var_s0, var_s1)));
            func_800A5720(var_s1);
        }
        var_s0->b3 |= 0x20;
        func_80098550();
        return;
    }

    state = var_s1;
    ASM_KEEP_NV(state);   /* MATCH pin: load-bearing for the whole function shape */
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
    ASM_SET(head_b);   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s2 = 0;
    ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    arg0->b85 = head_b_value;
    ASM_KEEP(var_s0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    arg0->field4C = var_s0;
    func_800A56E0(0x508);
    tail_index = var_s2;
    if (var_s0->b1 == 0x10) {
        arg0->b84 = D_800DD2E0[tail_index];
        arg0->b85 = D_800DD2D4[tail_index];
        if (tail_index != 0) {
            func_80048590(tail_index);
            func_800985E4();
            return;
        }
    } else {
        arg0->b84 = D_800DD2C4_index[tail_index];
        arg0->b85 = D_800DD2B4_index[tail_index];
        if (tail_index != 0) {
            func_80048568(tail_index);
            ASM_KEEP(var_s2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            if (var_s2 != 0) {
                return;
            }
        }
    }
    func_800483AC(1);
}
