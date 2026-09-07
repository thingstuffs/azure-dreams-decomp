#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A4ACC(void *, s32, s32);
extern s32 D_80083460;
extern u16 D_80083462;

void func_80175F44(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 var_a1;
    void *saved_arg0 = arg0;
    u8 field_71 = FIELD(arg0, volatile u8, 0x71);
    register s32 initial_mode ASM_REG("$3") = arg4;   /* MATCH pin: keeps a constant in a register as retail does */
    s32 raw_mode;

    field_71 &= 0x7F;
    ASM_KEEP(field_71);   /* MATCH pin: retail schedule: same instructions, different order without it */
    raw_mode = initial_mode;
    ASM_KEEP_NV(initial_mode);   /* MATCH pin: retail register colouring depends on it */
    initial_mode = (s16)initial_mode;
    FIELD(arg0, u8, 0x71) = field_71;
    if (initial_mode != 2) {
        u8 *state = (u8 *)&D_80083460;

        var_a1 = FIELD(state, u16, 2);
        if (var_a1 & 0x2000) {
            goto reject_saved;
        }
        if (FIELD(state, void *, 0xC) == arg0) {
            goto accepted;
        }
        if (FIELD(state, void *, 0xC) != 0) {
            goto reject_arg0;
        }
        if (FIELD(state, void *, 0x10) != 0) {
            goto reject_arg0;
        }
        if (!(var_a1 & 8)) {
            goto accepted;
        }

reject_arg0:
        FIELD(arg0, u8, 0x9A) = 14;
        goto done;
    }

    var_a1 = (s32)&D_80083460;
    if (FIELD((void *)var_a1, u16, 2) & 0x2000) {
        goto reject_saved;
    }
    if (FIELD((void *)var_a1, s16, 0xA) == 0) {
        goto increment_state;
    }

reject_saved:
    FIELD(saved_arg0, u8, 0x9A) = 14;
    goto done;

increment_state:
    FIELD((void *)var_a1, s16, 0xA) =
        (u16)FIELD((void *)var_a1, s16, 0xA) + 1;

accepted:
    {
    s32 mode = (s16)raw_mode;

    if (mode == 0) {
        void *state = (u8 *)&D_80083462 - 2;
        FIELD(state, u16, 0xA)++;
    }
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg0, s8, 0x9A) = 0x19;
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, s8, 0xB3) = 0;
    FIELD(arg0, s8, 0xB1) = 0;
    FIELD(arg0, s8, 0xB2) = 0;
    FIELD(arg0, s8, 0xB4) = raw_mode;
    if (mode == 0) {
        ASM_KEEP(mode);   /* MATCH pin: retail basic-block layout depends on it */
        func_800A4ACC(saved_arg0, mode, raw_mode);
        FIELD(saved_arg0, u8, 0x6D)--;
    }
    }

done:
    return;
}

/* MECHANISM: A 0x18 frame holds saved arg0 in s0 while a0 stays live for stores.
   Volatile field71 + guarded v1 liveness orders lbu/lw/andi and splits raw mode to a2.
   Local reject joins preserve a0/s0 bases; the signed-mode keep preserves a1 at jal. */
