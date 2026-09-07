#include "common.h"

typedef struct S_80171D80_0 {
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
} S_80171D80_0;   /* arg3 in func_80171D80 */

typedef struct S_80171D80_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171D80_1;   /* arg2 in func_80171D80 */

typedef struct S_80171D80_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171D80_2;   /* arg0 in func_80171D80 */



extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern s16 D_80083228;
extern volatile u16 D_80083460[];
extern u8 D_8017386C[];

/* Attempt an actor transition and update its state and sprite on success. */
s32 func_80171D80(void *state, s32 action_id, void *sprite, void *actor)
{
    volatile u16 *status;
    s32 transitioned;
    s32 target;

    ((S_80171D80_0 *)actor)->unk_71 &= 0x7F;
    status = D_80083460;
    transitioned = 0;
    if (((volatile u16 *)status)[1] & 0x2000) {
        goto abort_transition;
    }
    target = func_800A04F0(actor, ((S_80171D80_1 *)sprite)->unk_24,
                           ((S_80171D80_1 *)sprite)->unk_25, ((S_80171D80_0 *)actor)->unk_2A);
    if ((func_800A2CB8(actor, target) << 16) == 0) {
        goto return_zero;
    }
    {
        u16 status_flags = status[1];

        if (status_flags & 0x2000) {
            return -1;
        }
        if (!(((S_80171D80_0 *)actor)->unk_46 & 0x8000) && (status_flags & 8)) {
            return -1;
        }
    }
    if ((s16)(-func_800A0134(target, actor) + 0x40) >= 0x81U) {
        return transitioned;
    }

    transitioned = 1;
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
    {
        u16 state_flags;

        state_flags = ((S_80171D80_2 *)state)->unk_98;
        ((S_80171D80_2 *)state)->unk_9B = 0;
        ((S_80171D80_2 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((S_80171D80_2 *)state)->unk_9A = 0x17;
            ((S_80171D80_0 *)actor)->unk_84 = 0x10;
            ((S_80171D80_0 *)actor)->unk_85 = 0x10;
        } else {
            ((S_80171D80_2 *)state)->unk_9A = 0x11;
            ((S_80171D80_0 *)actor)->unk_84 = 0x7C;
            ((S_80171D80_0 *)actor)->unk_85 = 0;
        }
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017386C;
    func_80047784(sprite,
                  D_8017386C[((D_80083228 + ((S_80171D80_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
                  0);
    ((S_80171D80_0 *)actor)->unk_6D--;
    if (((S_80171D80_2 *)state)->unk_9A != 0x11) {
        return transitioned;
    }
    func_8009C93C(actor, sprite, ((S_80171D80_0 *)actor)->unk_2A, 1, 0);
    return transitioned;

return_zero:
    return 0;
}
