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
    register u8 *state ASM_REG("$16");
    register u8 *page ASM_REG("$2");
    register void *call_arg ASM_REG("$4");
    s32 index;

    call_arg = arg1;
    ASM_KEEP_NV(call_arg);
    page = (u8 *)0x80080000;
    ASM_KEEP_NV(page);
    state = page + 0x3160;
    func_80095544(call_arg);
    ASM_KEEP_NV(state);
    {
        register u8 *expected ASM_REG("$2");
        void *actual;

        expected = (u8 *)0x800A0000;
        ASM_KEEP_NV(expected);
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
        register s32 current ASM_REG("$4");
        register s32 goal ASM_REG("$5");
        register s32 distance ASM_REG("$6");
        s16 result;

        current = *(s16 *)((u8 *)arg0 + 0x18);
        ASM_KEEP_NV(current);
        goal = *(s16 *)((u8 *)arg0 + 0x10);
        ASM_KEEP_NV(goal);
        ASM_CLOBBER("$6");
        distance = 0x200;
        ASM_KEEP_NV(distance);
        result = func_80094AA0(current, goal, distance);
        ASM_SCHED_BARRIER();
        *(s16 *)((u8 *)arg0 + 0x18) = result;
    }
    ASM_MEM_BARRIER();
    ASM_SCHED_BARRIER();
    index = func_80095360(*(s16 *)((u8 *)arg0 + 0x18));
    if (*(s16 *)((u8 *)arg0 + 0x12) != index) {
        func_800489F4(arg2,
                      *(u8 *)(*(u8 **)((u8 *)arg0 + 0x1C) + index),
                      *(s8 *)((u8 *)arg2 + 4), 0);
        *(s16 *)((u8 *)arg0 + 0x12) = index;
    }
    {
        s16 *table = D_800D01F8;

        ASM_USE(table);
        if (table[index] != 0) {
            u16 bit_value = *(u16 *)((u8 *)arg2 + 0x14) | 1;

            ASM_TAILSLOT_PIN_TIED(bit_value);
            ASM_SCHED_BARRIER();
            func_800A584C();
            return;
        }
    }
    *(u16 *)((u8 *)arg2 + 0x14) &= 0xFFFE;
    ASM_MEM_BARRIER();
    func_80048AC8(arg2, 0);
    ASM_MEM_BARRIER();
    {
        u8 *state2 = D_80100D98;

        ASM_KEEP(state2);
        func_800A48B0(state2, arg1);
        *(s32 *)(state2 + 8) = 0;
    }
}
