#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80171ECC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171ECC_1;   /* source in func_80171ECC */




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
    register void *source ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 result;
    u16 *status;
    volatile long long frame_pad;

    source = arg2;
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 &= 0x7F;
    status = (u16 *)&D_80083460;
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    result = func_800A04F0(arg3, ((S_80171ECC_1 *)source)->unk_24,
                           ((S_80171ECC_1 *)source)->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }
    if (status[1] & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) && (status[1] & 8)) {
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
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0x11;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_84.as_u8 = 0x7C;
    ((Rec_D_800E3D7C *)arg3)->unk_85.as_u8 = 0;
    (*(u8 * *)((u8 *)source + 0x2C)) = D_80174214;
    func_80047784(
        source,
        D_80174214[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    func_8009C93C(arg3, source, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
    return 1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   A volatile eight-byte frame object raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */
