#include "common.h"


extern s32 func_800AB1C0(void);
extern void func_800A4ACC(void *);
extern void func_800CAA94(void *, s32, s32);
extern void func_800CAB88(void);

extern u16 D_80013714;
extern u16 D_80083462;
extern u8 D_800C9F34;


typedef struct S_800CAAC8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
} S_800CAAC8_0;   /* entity in func_800CAAC8 */

typedef struct S_800CAAC8_1 {
    u8 pad_00[0x71];
    u8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800CAAC8_1;   /* actor in func_800CAAC8 */

void func_800CAAC8(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
    void *entity = arg0;
    register s32 value1 ASM_REG("$18") = arg1;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 value2 ASM_REG("$19") = arg2;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *actor ASM_REG("$16") = arg3;   /* MATCH pin: load-bearing for the whole function shape */
    u16 count;

    if (func_800AB1C0() == 0) {
        goto check_flag;
    }

    func_800A4ACC(actor);
    count = ((S_800CAAC8_0 *)entity)->unk_B6 - 1;
    ((S_800CAAC8_0 *)entity)->unk_B6 = count;

    if ((count << 16) > 0) {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        if (!(D_80013714 & 8)) {
            goto set_callback;
        }
    }

    if (((S_800CAAC8_1 *)actor)->unk_71 != ((S_800CAAC8_1 *)actor)->unk_8A) {
        goto set_callback;
    }

    func_800CAA94(entity, value1, value2);
    func_800CAB88();
    return;

set_callback:
    ((S_800CAAC8_0 *)entity)->unk_8C = &D_800C9F34;

check_flag:
    if (D_80083462 & 0x80) {
        ((S_800CAAC8_0 *)entity)->unk_92 = -0x20;
    }
}

/* MECHANISM: Pinned arguments preserve the retail 0x28 frame and s1/s2/s3/s0 roles.
   ASM_SCHED_BARRIER keeps the blez delay slot empty instead of stealing the flag-page lui.
   Both 0x71 and 0x8A comparison fields use the actor base held in s0. */
