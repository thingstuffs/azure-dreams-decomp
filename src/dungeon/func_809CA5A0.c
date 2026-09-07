#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171DA0_1;   /* held_arg2 in func_80171DA0 */




extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80173C7C;

s32 func_80171DA0(Rec_func_800A9E70_arg0 *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 result;
    u16 flags;
    u8 top_flags;
    s32 held_arg1;
    register void *held_arg2 ASM_REG("$19");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 status_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 *status ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    volatile s32 frame_pad[2];

    top_flags = ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8;
    held_arg1 = arg1;
    top_flags &= 0x7F;
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = top_flags;
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    status_page = 0x80080000U;
    ASM_KEEP(status_page);   /* MATCH pin: load-bearing for the whole function shape */
    status = (u16 *)(status_page + 0x3460);
    ASM_KEEP(status);   /* MATCH pin: load-bearing for the whole function shape */
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    held_arg2 = arg2;

    result = func_800A04F0(arg3, ((S_80171DA0_1 *)held_arg2)->unk_24,
                           ((S_80171DA0_1 *)held_arg2)->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }

    flags = status[1];
    if (flags & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) && (flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(result, arg3) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    return -1;

transition_ok:
    {
        s32 angle;
        register u32 scratch ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *effect;

        arg0->unk_9A.as_u8 = 0x11;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        scratch = 0x7C;
        effect = &D_80173C7C;
        arg0->unk_9B.as_u8 = 0;
        arg0->unk_8C = 0;
        ((Rec_D_800E3D7C *)arg3)->unk_84.as_u8 = scratch;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        scratch = 0x80080000U;
        ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((Rec_D_800E3D7C *)arg3)->unk_85.as_u8 = 0;
        ((S_80171DA0_1 *)held_arg2)->unk_2C = effect;
        scratch = (s32)*(s16 *)(scratch + 0x3228);
        angle = ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16;
        scratch += angle;
        scratch += 0x100;
        scratch = ((s32)scratch >> 9) & 7;
        scratch += (u32)effect;
        func_80047784(held_arg2,
                      *(u8 *)scratch,
                      0);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
        func_8009C93C(arg3, held_arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
        return 1;
    }
}

/* MECHANISM: An addressless 8-byte frame object plus held s2 status base gives the 0x40 frame;
   split s5/s3 input live ranges and a zero-byte abort fence reproduce the prologue and local CFG.
   A held a1 effect base and successive v0 scratch roles close the success addressing chain. */
