#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 rand();
extern s16 func_800BCB04();
extern s16 D_80025338;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;

void func_81814C48(void *arg0, void *arg1, void *arg2)
{
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 accum;
    s32 random;
    register s32 call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register s32 tail_offset ASM_REG("$4");

    call_a2 = FIELD(arg1, u16, 0xA);
    call_a0 = FIELD(arg1, u16, 2);
    call_a1 = FIELD(arg1, u16, 6);
    D_80025338 = 1;
    ASM_KEEP(call_a0);
    ASM_KEEP(call_a1);
    ASM_KEEP(call_a2);
    if ((s16)FIELD(arg1, u16, 0xA) <
        func_800BCB04(call_a0, call_a1, (s16)(call_a2 + 2))) {
        temp_a0 = ((*(s16 *)(&D_8006CCD8 + (FIELD(arg0, s16, 0x14) * 2)) *
                    FIELD(arg0, s16, 0x32)) << 9) +
                  (rand() & 0xFFFF);
        accum = FIELD(arg1, s32, 0) + temp_a0;
        FIELD(arg1, s32, 0) = accum;
        temp_a0_2 = ((*(s16 *)(&D_8006CCE8 + (FIELD(arg0, s16, 0x14) * 2)) *
                      FIELD(arg0, s16, 0x32)) << 9) +
                    (rand(temp_a0) & 0xFFFF);
        accum = FIELD(arg1, s32, 4) + temp_a0_2;
        FIELD(arg1, s32, 4) = accum;
        random = rand(temp_a0_2);
        tail_offset = 0xFFFE0000;
        ASM_KEEP(tail_offset);
        accum = FIELD(arg1, s32, 8) + tail_offset;
        accum -= random & 0xFFF;
        FIELD(arg1, s32, 8) = accum;
    }
    temp_v0 = (u16)FIELD(arg0, s16, 0x32) - 8;
    FIELD(arg0, s16, 0x32) = temp_v0;
    if (((temp_v0 << 16) <= 0) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Guarded a0/a1/a2 call-argument pins fence D_80025338 without
   growing the retail 0x20 s1/s0/s2 frame. Byte table bases with s16 loads
   plus explicit accumulator RMWs place each lw before mflo. A tail a0
   constant pin and direct D_800814A0 scalar RMW remove the two cascades. */
