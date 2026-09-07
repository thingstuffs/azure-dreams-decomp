#include "common.h"

/* S_80082E60: shared global state struct; field_16 (u16) has bit 0x2 set here.
 * Same struct family as src/code2.c / src/w_80041818.c's D_80082E60. */
struct S_80082E60 {
    char pad0[0x16];
    u16 field_16;
};
extern struct S_80082E60 D_80082E60;

extern void func_80025D34();
extern void func_80027BF4(void);
extern void func_80040AA0();
extern void func_800439F8(void);

void func_800251A4(void *arg0) {
    s16 var_a1;
    s32 var_a0;
    u16 var_v1;
    /* D_80013714 and D_80010208 sit on the same 64K page; retail keeps ONE
     * lui (0x8001) live in a callee-saved reg ($s1) across both accesses and
     * across the two intervening calls. Pin the page base to a saved hard
     * register so it survives the calls instead of being rematerialized. */
    u8 *pg = (u8 *)0x80010000;

    func_80027BF4();
    var_a1 = 1;
    if (*(s32 *)((char *)arg0 + 0x44) == 0) {
        var_a1 = 3;
    }
    var_v1 = D_80082E60.field_16;
    *(s16 *)(pg + 0x3714) = var_a1;
    D_80082E60.field_16 = var_v1 | 2;
    func_80025D34(arg0 - 0x20, var_a1);
    func_800439F8();
    var_a0 = 6;
    if (*(u16 *)(pg + 0x208) != 0) {
        var_a0 = 5;
    }
    func_80040AA0(var_a0);
}
