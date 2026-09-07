#include "common.h"

extern u8 D_80083160[];
extern s32 D_800A5A98;
extern s16 D_800D01F8[];
extern u8 D_80100D98[];

extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 func_80094AA0(s32, s32, s32);
extern s32 func_80095360(s16);
extern void func_80095544(void *);
extern void func_800A48B0(void *, void *);
extern void func_800A57D0(s16, s32, s32);
extern void func_800A584C(void);

void func_800A573C(void *arg0, void *arg1, void *arg2) {
    u8 *state;
    u8 *page;
    register void *call_arg ASM_REG("$4");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 index;

    call_arg = arg1;
    page = (u8 *)0x80080000;
    ASM_KEEP_NV(page);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    state = page + 0x3160;
    func_80095544(call_arg);
    ASM_KEEP_NV(state);   /* MATCH pin: keeps a statement from moving across a call/branch */
    {
        u8 *expected;
        void *actual;

        expected = (u8 *)0x800A0000;
        ASM_KEEP_NV(expected);   /* MATCH pin: load-bearing for the whole function shape */
        actual = *(void **)arg0;
        expected += 0x5A98;
        if (actual == expected) {
            if (*(s32 *)(state + 8) & 0x2000) {
                return func_800A57D0(*(s16 *)((u8 *)arg0 + 0x18),
                                     *(s16 *)((u8 *)arg0 + 0x10) - 0x200,
                                     0x200);
            }
            if (*(s32 *)(state + 8) & 0x8000) {
                return func_800A57D0(*(s16 *)((u8 *)arg0 + 0x18),
                                     *(s16 *)((u8 *)arg0 + 0x10) + 0x200,
                                     0x200);
            }
        }
    }
    {
        s32 current;
        s32 goal;
        s32 distance;
        s16 result;

        current = *(s16 *)((u8 *)arg0 + 0x18);
        goal = *(s16 *)((u8 *)arg0 + 0x10);
        ASM_CLOBBER("$6");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        distance = 0x200;
        ASM_KEEP_NV(distance);   /* MATCH pin: retail schedule: same instructions, different order without it */
        result = func_80094AA0(current, goal, distance);
        *(s16 *)((u8 *)arg0 + 0x18) = result;
    }
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    index = func_80095360(*(s16 *)((u8 *)arg0 + 0x18));
    if (*(s16 *)((u8 *)arg0 + 0x12) != index) {
        func_800489F4(arg2,
                      *(u8 *)(*(u8 **)((u8 *)arg0 + 0x1C) + index),
                      *(s8 *)((u8 *)arg2 + 4), 0);
        *(s16 *)((u8 *)arg0 + 0x12) = index;
    }
    {
        s16 *table = D_800D01F8;

        ASM_USE(table);   /* MATCH pin: retail delay-slot fill depends on it */
        if (table[index] != 0) {
            u16 bit_value = *(u16 *)((u8 *)arg2 + 0x14) | 1;

            ASM_TAILSLOT_PIN_TIED(bit_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800A584C();
            return;
        }
    }
    *(u16 *)((u8 *)arg2 + 0x14) &= 0xFFFE;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    func_80048AC8(arg2, 0);
    {
        u8 *state2 = D_80100D98;

        ASM_KEEP(state2);   /* MATCH pin: load-bearing for the whole function shape */
        func_800A48B0(state2, arg1);
        *(s32 *)(state2 + 8) = 0;
    }
}
