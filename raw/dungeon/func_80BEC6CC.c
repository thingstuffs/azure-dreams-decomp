#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80174214[];

s32 func_80171ECC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *source ASM_REG("$19");
    s32 result;
    u16 *status;
    volatile long long frame_pad;

    source = arg2;
    FIELD(arg3, u8, 0x71) &= 0x7F;
    status = (u16 *)&D_80083460;
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    ASM_KEEP(source);
    result = func_800A04F0(arg3, FIELD(source, u8, 0x24),
                           FIELD(source, u8, 0x25), FIELD(arg3, s16, 0x2A));
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }
    if (status[1] & 0x2000) {
        return -1;
    }
    if (!(FIELD(arg3, u16, 0x46) & 0x8000) && (status[1] & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(result, arg3) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    return -1;

transition_ok:
    FIELD(arg0, u8, 0x9A) = 0x11;
    FIELD(arg0, u8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg3, u8, 0x84) = 0x7C;
    FIELD(arg3, u8, 0x85) = 0;
    FIELD(source, u8 *, 0x2C) = D_80174214;
    func_80047784(
        source,
        D_80174214[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_8009C93C(arg3, source, FIELD(arg3, s16, 0x2A), 1, 0);
    FIELD(arg3, u8, 0x6D)--;
    return 1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   A volatile eight-byte frame object raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */
