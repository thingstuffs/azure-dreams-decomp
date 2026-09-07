#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_800A8608(void *, void *, s32, s32, s32);
extern void func_800A7A18() __attribute__((noreturn));

extern s32 D_80083498;
extern s32 D_800A77AC;
extern s32 D_80083460;

s32 func_800A794C(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4,
                  s32 arg5, s32 arg6) {
    u8 *object;
    u8 *position;
    u8 *fields;
    u8 *state;
    s32 payload;
    s32 last;
    u16 count;
    register s32 result ASM_REG("$2");
    register u8 *callback ASM_REG("$2");

    object = func_800A8608(&D_80083498, arg3, 0, 0, 0);
#ifdef NON_MATCHING
    callback = (u8 *)&D_800A77AC;
#else
    callback = (u8 *)0x800A0000;
#endif
    if (object != 0) {
#ifndef NON_MATCHING
        ASM_KEEP(callback);
        callback += 0x77AC;
#endif
        FIELD(object, void *, 0x10) = callback;
        position = FIELD(object, u8 *, 8);
        FIELD(position, s16, 2) = (s16)((arg0 << 6) + 0x20);
        FIELD(position, s16, 6) = (s16)((arg1 << 6) + 0x20);
        FIELD(position, s16, 0xA) = arg2;

        fields = object + 0x20;
        payload = *arg3;
        FIELD(fields, s16, 0xA0) = 4;
        FIELD(fields, s16, 0xAA) = (s16)arg4;
        FIELD(fields, s16, 0xAC) = (s16)arg5;
        ASM_SCHED_BARRIER();
        last = arg6;
        ASM_KEEP(last);
        FIELD(fields, s32, 0x98) = payload;
        ASM_SCHED_BARRIER();
        state = (u8 *)&D_80083460;
        FIELD(fields, s16, 0xAE) = (s16)last;
        count = FIELD(state, u16, 0xA);
        result = (s32)object;
        count++;
        ASM_KEEP(result);
        FIELD(state, u16, 0xA) = count;
        func_800A7A18(state, object);
    }
    result = 0;
    ASM_KEEP(result);
    return result;
}

/* MECHANISM: s32 arg2 plus the early payload local produce the exact 0x30 frame
   and s0/s2/s3/s1 argument roles; barriers keep arg6/payload/state lifetimes exact.
   Guarded v0 page/result carriers split the callback la and expose the noreturn tail j. */
