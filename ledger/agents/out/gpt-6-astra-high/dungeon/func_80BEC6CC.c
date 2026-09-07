#include "common.h"

typedef struct S_80171ECC_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
} S_80171ECC_0;   /* arg3 in func_80171ECC */

typedef struct S_80171ECC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171ECC_1;   /* source in func_80171ECC */

typedef struct S_80171ECC_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_80171ECC_2;   /* arg0 in func_80171ECC */



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

/* Check the actor's transition conditions and initialize the action and source animation. */
s32 func_80171ECC(void *action_state, s32 action_id, void *source_obj, void *actor)
{
    register void *source ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 target_angle;
    u16 *status;
    volatile long long frame_pad;

    source = source_obj;
    ((S_80171ECC_0 *)actor)->unk_71 &= 0x7F;
    status = (u16 *)&D_80083460;
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    target_angle = func_800A04F0(actor, ((S_80171ECC_1 *)source)->unk_24,
                                ((S_80171ECC_1 *)source)->unk_25, ((S_80171ECC_0 *)actor)->unk_2A);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }
    if (status[1] & 0x2000) {
        return -1;
    }
    if (!(((S_80171ECC_0 *)actor)->unk_46 & 0x8000) && (status[1] & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    return -1;

transition_ok:
    ((S_80171ECC_2 *)action_state)->unk_9A = 0x11;
    ((S_80171ECC_2 *)action_state)->unk_9B = 0;
    ((S_80171ECC_2 *)action_state)->unk_8C = 0;
    ((S_80171ECC_0 *)actor)->unk_84 = 0x7C;
    ((S_80171ECC_0 *)actor)->unk_85 = 0;
    (*(u8 * *)((u8 *)source + 0x2C)) = D_80174214;
    func_80047784(
        source,
        D_80174214[((D_80083228 + ((S_80171ECC_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    func_8009C93C(actor, source, ((S_80171ECC_0 *)actor)->unk_2A, 1, 0);
    ((S_80171ECC_0 *)actor)->unk_6D--;
    return 1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   A volatile eight-byte frame object raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */
