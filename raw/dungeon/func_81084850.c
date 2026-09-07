#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, s32, s32, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80175F48;

s32 func_80172050(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    volatile u8 frame_pad[8];
    register void *out ASM_REG("$20");
    register s32 held_arg1 ASM_REG("$21");
    register void *info ASM_REG("$19");
    register void *actor ASM_REG("$16");
    register void *call_actor ASM_REG("$4");
    u16 *state;
    u8 *table;
    register s32 temp_v0 ASM_REG("$17");
    s32 raw_v0;
    s32 result;
    s32 actor84_value;
    u16 flags;

    out = arg0;
    actor = arg3;
    FIELD(actor, u8, 0x71) &= 0x7F;
    held_arg1 = arg1;
    ASM_KEEP(held_arg1);
    state = (u16 *)&D_80083460;
    ASM_KEEP(state);
    if (state[1] & 0x2000) {
        goto failure;
    }
    info = arg2;

    raw_v0 = func_800A04F0(actor, FIELD(info, u8, 0x24),
        FIELD(info, u8, 0x25), FIELD(actor, s16, 0x2A));
    call_actor = actor;
    ASM_KEEP(call_actor);
    temp_v0 = raw_v0;
    if ((func_800A2CB8(call_actor, temp_v0) << 16) == 0) {
        result = 0;
        goto done;
    }

    flags = state[1];
    if (flags & 0x2000) {
        result = -1;
        goto done;
    }
    if (!(FIELD(actor, u16, 0x46) & 0x8000)) {
        ASM_SCHED_BARRIER();
        if (flags & 8) {
            result = -1;
            goto done;
        }
    }

    if ((u16)(-func_800A0134(temp_v0, actor) + 0x3F) >= 0x7F) {
        result = 0;
        goto done;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        result = -1;
        goto done;
    }

    func_800C7930((u8 *)actor - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto success;
    }

failure:
    ASM_KEEP(state);
    result = -1;
    goto done;

success:
    FIELD(out, s8, 0x9A) = 0x11;
    actor84_value = 0x7C;
    FIELD(out, s8, 0x9B) = 0;
    FIELD(out, s32, 0x8C) = 0;
    ASM_KEEP(out);
    FIELD(actor, s8, 0x84) = actor84_value;
    FIELD(actor, s8, 0x85) = 4;
    table = &D_80175F48;
    FIELD(info, void *, 0x2C) = table;
    func_80047784(info,
        table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    call_actor = actor;
    ASM_KEEP(call_actor);
    FIELD(call_actor, u8, 0x6D)--;
    func_8009C93C(call_actor, info, FIELD(call_actor, s16, 0x2A), 1, 0);
    ASM_KEEP(info);
    ASM_KEEP(actor);
    result = 1;

done:
    return result;
}

/* MECHANISM: The eight-byte frame object and pinned long-lived roles reproduce
   retail's 0x40 frame; the held D_80083460 base remains in s2 across calls.
   A fall-through schedule barrier blocks the flags andi, while removing the
   target-head temp_v0 keep lets dbr duplicate move a0,s1 into branch slot R#42. */
