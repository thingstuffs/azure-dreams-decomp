#include "common.h"

extern void func_800483AC(s32);
extern void func_800485B8(s32);
extern u8 *func_80097F84(u8 *, void *, void *, s32);
extern void func_80098804(void);
extern void func_80098844(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099368(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);

extern u8 D_800DD2EC[];
extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern u8 D_800E0874[];
extern u8 D_800E089C[];
extern u8 D_800E08AB[];
extern u8 D_800E08BA[];

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80098614(void *arg0, u8 *arg1)
{
    u8 *current;
    u8 *object;
    u8 *table;
    s32 flags;
    s32 id;
    s32 check;
    s32 result;
    s32 state;

    current = arg1;
    state = 0;

    if (current != 0) {
        current = func_80097F84(current, D_800E07C0, D_800E07D3, 0);
        if (current == 0) {
            return;
        }
    }

    object = FIELD(arg0, u8 *, 0x50);
    if (object != 0) {
        flags = object[3];
        if (flags & 0x40) {
            func_800A56E0(0x70A);
            state = func_800990FC();
            result = func_8009929C(8, state);
            result = func_80099368(object, result);
            result = func_80099194(D_800E0874, result);
            func_80099290(result);
            func_800A5720(state);
            func_80098844();
            return;
        }
        object[3] = flags & 0xDF;
        if (object == current) {
            current = 0;
        }
        state = 1;
    }

    check = state;
    if (current != 0) {
        current[3] &= 0x7F;
        id = current[0];
        state = func_800990FC();
        result = func_8009929C(8, state);
        result = func_80099368(current, result);
        result = func_80099194(D_800E089C, result);
        func_80099290(result);
        func_800A5720(state);

        if (current[3] & 0x40) {
            FIELD(arg0, s32, 0x1C) |= 0x800;
            func_800A56E0(0x70A);
            state = func_800990FC();
            result = func_80099368(current, state);
            result = func_80099194(D_800E08AB, result);
            func_80099290(result);
            func_800A5720(state);
        }

        ASM_KEEP(id);
        current[3] |= 0x20;
        func_80098804();
        return;
    }

    ASM_KEEP(check);
    ASM_KEEP(current);
    id = 0;
    if (check != 0) {
        state = func_800990FC();
        result = func_8009929C(8, state);
        result = func_80099368(FIELD(arg0, void *, 0x50), result);
        result = func_80099194(D_800E08BA, result);
        func_80099290(result);
        func_800A5720(state);
    }

    ASM_KEEP(id);
    FIELD(arg0, u8 *, 0x50) = current;
    func_800A56E0(0x508);
    {
        register s32 call_id ASM_REG("$4");

        call_id = id;
        ASM_KEEP(call_id);
        table = D_800DD2EC;
        ASM_KEEP(table);
        FIELD(arg0, u8, 0x86) = *(u8 *)((u32)call_id + (u32)table);
        if (call_id != 0) {
            func_800485B8(call_id);
            func_80098844();
            return;
        }
    }
    ASM_CLOBBER("$4");
    func_800483AC(0);
}

/* MECHANISM: Ordered zero-byte check/current fences preserve the $v0 predicate copy
   and invalidate current==0 before the delayed $s1 literal while retaining the 0x28 frame.
   An index-first u32 address sum fixes the tail addu; ASM_CLOBBER reloads the final $a0. */
