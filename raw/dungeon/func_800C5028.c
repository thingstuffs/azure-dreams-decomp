#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s32 D_80083460;

extern s32 func_8009B4B0(void *, u8, u8);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, void *, s32, s32);

s32 func_800CA788(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 call_result;
    s32 mask;
    u8 *object;
    u8 *actor;
    register void *held_arg1 ASM_REG("$21");
    register void *held_arg2 ASM_REG("$18");
    u8 *global_base;
    u16 flags;

    object = arg0;
    actor = arg3;
    actor[0x71] &= 0x7F;
    held_arg1 = arg1;
    ASM_KEEP(held_arg1);
    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, u16, 2) & 0x2000) {
        goto return_negative;
    }
    held_arg2 = arg2;
    ASM_KEEP(held_arg2);

    FIELD(actor, s32, 0x14) |= 0x2000;
    FIELD(actor, s32, 0x1C) |= 0x2000;
    call_result = func_8009B4B0(actor, FIELD(held_arg2, u8, 0x24), FIELD(held_arg2, u8, 0x25));
    mask = ~0x2000;
    FIELD(actor, s32, 0x14) &= mask;
    FIELD(actor, s32, 0x1C) &= mask;
    flags = FIELD(global_base, u16, 2);
    if (!(flags & 0x2000)) {
        goto check_flag_8;
    }
return_negative:
    ASM_SCHED_BARRIER();
    return -1;
check_flag_8:
    if (flags & 8) {
        return -1;
    }

    if ((u32)((-func_800A0134(call_result, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930(actor - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    {
        register void *call_a0 ASM_REG("$4");
        register void *call_a1 ASM_REG("$5");
        register s32 call_a2 ASM_REG("$6");
        register s32 call_a3 ASM_REG("$7");
        s32 word_14;
        s32 word_1C;

        call_a0 = actor;
        ASM_KEEP(call_a0);
        call_a1 = held_arg2;
        ASM_KEEP(call_a1);
        object[0x9B] = 0;
        FIELD(object, s32, 0x8C) = 0;
        object[0x9A] = 0x11;
        call_a2 = FIELD(actor, s16, 0x2A);
        ASM_KEEP(call_a2);
        actor[0x84] = 0x80;
        ASM_SCHED_BARRIER();
        word_14 = FIELD(actor, s32, 0x14);
        word_1C = FIELD(actor, s32, 0x1C);
        ASM_SCHED_BARRIER();
        call_a3 = 0;
        ASM_KEEP(call_a3);
        actor[0x85] = 0;
        word_14 |= 0x2000;
        word_1C |= 0x2000;
        FIELD(actor, s32, 0x14) = word_14;
        FIELD(actor, s32, 0x1C) = word_1C;
        ASM_SCHED_BARRIER();
        func_8009C93C(call_a0, call_a1, call_a2, call_a3, 0);
    }
    FIELD(actor, s32, 0x14) &= mask;
    FIELD(actor, s32, 0x1C) &= mask;
    actor[0x6D]--;
    return 1;
}
