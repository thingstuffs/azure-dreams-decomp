#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_800814A0[3];

extern void func_8009A028();
extern void func_8009A21C();
extern void func_800A2B04();
extern void func_800A32A4();
extern s16 func_800BCB04();


typedef struct S_800AC5C8_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_800AC5C8_0;   /* arg0 in func_800AC5C8 */

typedef struct S_800AC5C8_1_pre {
    u16 unk_00;
} S_800AC5C8_1_pre;   /* the 0x2 bytes before arg3 in func_800AC5C8, addressed as arg3[-1] */



typedef struct S_800AC5C8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AC5C8_3;   /* arg2 in func_800AC5C8 */

s32 func_800AC5C8(S_800AC5C8_0 *arg0, Rec_D_800E3D7C *arg1, S_800AC5C8_3 *arg2, void *arg3) {
    s32 force;
    u16 count;
    s32 state;
    u8 x;
    u8 y;

    state = arg0->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    {
        s32 rv_low;

        rv_low = 0;
        ASM_KEEP(rv_low);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return rv_low;
    }

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    {
        s32 rv_high;

        rv_high = 0;
        ASM_KEEP(rv_high);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return rv_high;
    }

state_0:
        ((Rec_D_80082E80 *)arg3)->unk_6A = ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v & 0xFFF;
        arg0->unk_9B++;
        /* fall through */

state_1:
        ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v += 0x200;
        arg1->unk_14.as_s32 -= 0x10000;

        count = arg0->unk_96 - 1;
        arg0->unk_96 = count;
        if ((s16)count > 0) {
            return 0;
        }

        arg1->unk_14.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg0->unk_96 = 0x10;

        if (!(((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v & 0x4000)) {
            D_80083460.field_A--;
            func_800A32A4(arg3);
            func_8009A028(arg3);
            ((S_800AC5C8_1_pre *)arg3)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
            goto return_zero;
        }

        ((Rec_D_80082E80 *)arg3)->unk_88.as_u16 = func_800BCB04(
            (arg2->unk_24 << 6) | 0x20,
            (arg2->unk_25 << 6) | 0x20,
            -0x400);
        arg0->unk_98 &= 0xFFF7;
        ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v &= 0xFFFEFFFF;
        arg0->unk_96 = 0x10;
        arg0->unk_9B++;
        goto return_zero;

state_2:
        ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v += 0x200;
        count = arg0->unk_96 - 1;
        arg0->unk_96 = count;
        if ((s16)count > 0) {
            return 0;
        }

        arg0->unk_90 = 0;
        x = arg2->unk_24;
        y = arg2->unk_25;
        if (((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v & 0x2000) {
            force = 0x300;
        } else {
            force = 0x3000;
        }
        func_8009A21C(x, y, force);
        {
            D_80083460_t *status;

            status = &D_80083460;
            status->field_A--;
        }
        {
            u16 restored;
            register s32 rv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            restored = ((Rec_D_80082E80 *)arg3)->unk_6A;
            ASM_USE(restored);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            rv = 1;
            ASM_USE(rv);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v = restored;
            return rv;
        }
return_zero:
    ASM_SCHED_BARRIER(); /* MATCH: keep the zero assignment in the shared tail after both state-1 stores. */
    return 0;
}

/* MECHANISM: vars=0 frame holds arg0/arg2/arg3 and 0x10 in s1/s2/s0/s3.
   A signed ladder duplicates the two v0=0 noreturn default tails instead of merging them.
   Non-overlap v0 status/rv and v1 restored pins reproduce the case-2 live ranges.
   Ordered ASM_USE plus the returning alias/return 0 retains lhu;li;j;sh and dead move v0,zero. */
