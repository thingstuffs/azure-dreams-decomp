#include "common.h"

typedef struct S_800A794C_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800A794C_0;   /* object in func_800A794C */

typedef struct S_800A794C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800A794C_1;   /* position in func_800A794C */

typedef struct S_800A794C_2 {
    u8 pad_00[0x98];
    s32 unk_98;
    u8 pad_9C[0x4];
    s16 unk_A0;
    u8 pad_A2[0x8];
    s16 unk_AA;
    s16 unk_AC;
    s16 unk_AE;
} S_800A794C_2;   /* fields in func_800A794C */

typedef struct S_800A794C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800A794C_3;   /* state in func_800A794C */



extern void *func_800A8608(void *, void *, s32, s32, s32);

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
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *callback ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    object = func_800A8608(&D_80083498, arg3, 0, 0, 0);
#ifdef NON_MATCHING
    callback = (u8 *)&D_800A77AC;
#else
    callback = (u8 *)0x800A0000;
#endif
    if (object != 0) {
#ifndef NON_MATCHING
        ASM_KEEP(callback);   /* MATCH pin: keeps a statement from moving across a call/branch */
        callback += 0x77AC;
#endif
        ((S_800A794C_0 *)object)->unk_10 = callback;
        position = ((S_800A794C_0 *)object)->unk_08;
        ((S_800A794C_1 *)position)->unk_02 = (s16)((arg0 << 6) + 0x20);
        ((S_800A794C_1 *)position)->unk_06 = (s16)((arg1 << 6) + 0x20);
        ((S_800A794C_1 *)position)->unk_0A = arg2;

        fields = object + 0x20;
        payload = *arg3;
        ((S_800A794C_2 *)fields)->unk_A0 = 4;
        ((S_800A794C_2 *)fields)->unk_AA = (s16)arg4;
        ((S_800A794C_2 *)fields)->unk_AC = (s16)arg5;
        last = arg6;
        ((S_800A794C_2 *)fields)->unk_98 = payload;
        state = (u8 *)&D_80083460;
        ((S_800A794C_2 *)fields)->unk_AE = (s16)last;
        count = ((S_800A794C_3 *)state)->unk_0A;
        result = (s32)object;
        count++;
        ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_800A794C_3 *)state)->unk_0A = count;
        return;
    }
    result = 0;
    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
    return result;
}

/* MECHANISM: s32 arg2 plus the early payload local produce the exact 0x30 frame
   and s0/s2/s3/s1 argument roles; barriers keep arg6/payload/state lifetimes exact.
   Guarded v0 page/result carriers split the callback la and expose the noreturn tail j. */
