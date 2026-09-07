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

s32 func_80171D80(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    volatile u16 *status;
    s32 actor;
    s32 result;

    ((S_80171D80_0 *)arg3)->unk_71 &= 0x7F;
    status = D_80083460;
    actor = 0;
    if (((volatile u16 *)status)[1] & 0x2000) {
        goto abort_transition;
    }
    result = func_800A04F0(arg3, ((S_80171D80_1 *)arg2)->unk_24,
                           ((S_80171D80_1 *)arg2)->unk_25, ((S_80171D80_0 *)arg3)->unk_2A);
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        goto return_zero;
    }
    {
        u16 status_flags = status[1];

        if (status_flags & 0x2000) {
            return -1;
        }
        if (!(((S_80171D80_0 *)arg3)->unk_46 & 0x8000) && (status_flags & 8)) {
            return -1;
        }
    }
    if ((s16)(-func_800A0134(result, arg3) + 0x40) >= 0x81U) {
        return actor;
    }

    actor = 1;
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
    {
        u16 flags;

        flags = ((S_80171D80_2 *)arg0)->unk_98;
        ((S_80171D80_2 *)arg0)->unk_9B = 0;
        ((S_80171D80_2 *)arg0)->unk_8C = 0;
        if (flags & 0x8000) {
            ((S_80171D80_2 *)arg0)->unk_9A = 0x17;
            ((S_80171D80_0 *)arg3)->unk_84 = 0x10;
            ((S_80171D80_0 *)arg3)->unk_85 = 0x10;
        } else {
            ((S_80171D80_2 *)arg0)->unk_9A = 0x11;
            ((S_80171D80_0 *)arg3)->unk_84 = 0x7C;
            ((S_80171D80_0 *)arg3)->unk_85 = 0;
        }
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017386C;
    func_80047784(arg2,
                  D_8017386C[((D_80083228 + ((S_80171D80_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                  0);
    ((S_80171D80_0 *)arg3)->unk_6D--;
    if (((S_80171D80_2 *)arg0)->unk_9A != 0x11) {
        return actor;
    }
    func_8009C93C(arg3, arg2, ((S_80171D80_0 *)arg3)->unk_2A, 1, 0);
    return actor;

return_zero:
    return 0;
}
