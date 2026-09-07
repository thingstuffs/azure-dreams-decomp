#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800AB1C0(void);
extern void func_800A4ACC(void *);
extern void func_800CAA94(void *, s32, s32);
extern void func_800CAB88(void);

extern u16 D_80013714;
extern u16 D_80083462;
extern u8 D_800C9F34;

void func_800CAAC8(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
    register void *entity ASM_REG("$17") = arg0;
    register s32 value1 ASM_REG("$18") = arg1;
    register s32 value2 ASM_REG("$19") = arg2;
    register void *actor ASM_REG("$16") = arg3;
    u16 count;

    if (func_800AB1C0() == 0) {
        goto check_flag;
    }

    func_800A4ACC(actor);
    count = FIELD(entity, u16, 0xB6) - 1;
    FIELD(entity, u16, 0xB6) = count;

    if ((count << 16) > 0) {
        ASM_SCHED_BARRIER();
        if (!(D_80013714 & 8)) {
            goto set_callback;
        }
    }

    if (FIELD(actor, u8, 0x71) != FIELD(actor, s16, 0x8A)) {
        goto set_callback;
    }

    func_800CAA94(entity, value1, value2);
    func_800CAB88();
    return;

set_callback:
    FIELD(entity, void *, 0x8C) = &D_800C9F34;

check_flag:
    if (D_80083462 & 0x80) {
        FIELD(entity, s16, 0x92) = -0x20;
    }
}

/* MECHANISM: Pinned arguments preserve the retail 0x28 frame and s1/s2/s3/s0 roles.
   ASM_SCHED_BARRIER keeps the blez delay slot empty instead of stealing the flag-page lui.
   Both 0x71 and 0x8A comparison fields use the actor base held in s0. */
