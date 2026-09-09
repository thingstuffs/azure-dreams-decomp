#include "common.h"

typedef struct S_800B260C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
} S_800B260C_0;   /* base in func_800B260C */

typedef struct S_800B260C_1 {
    u8 pad_00[0x10];
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
} S_800B260C_1;   /* arg0 in func_800B260C */



extern u8 D_80083160[];

extern void SD_Call(s32);
extern void func_800B1DCC(void *);
extern void func_800B1F80(void *, s32);
extern void func_800B2068(void *);
extern void func_800B2394(void *, s32);
extern s32 func_800B2400(void *);
extern void func_800B25D8(void *);
extern void func_800B2CE8(void *);

void func_800B260C(u8 *arg0) {
    u8 *base = D_80083160;
    s32 input = ((S_800B260C_0 *)base)->unk_08;
    s32 buttons;
    s32 action = 0;
    s32 result;
    s32 count;
    s32 input2;

    if (input == 0) {
        goto finish;
    }

    buttons = ((S_800B260C_0 *)base)->unk_10.s;
    if (buttons & 0x20) {
        SD_Call(0x515);
        func_800B2CE8(arg0 - 0x20);
        goto finish;
    }
    if (buttons & 0x40) {
        result = func_800B2400(arg0);
        if (result == 0) {
            SD_Call(0x503);
            goto update;
        }
        if (result != 3) {
            goto finish;
        }
        SD_Call(0x506);
        goto finish;
    }
    if (buttons & 0x80) {
        SD_Call(0x503);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        goto finish;
    }
    if (buttons & 0x10) {
        SD_Call(0x503);
        func_800B25D8(arg0);
update:
        func_800B2068(arg0);
        goto finish;
    }
    if (buttons & 4) {
        func_800B2394(arg0, 0);
        goto finish;
    }
    if (buttons & 1) {
        func_800B2394(arg0, 1);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        goto finish;
    }
    if ((input & 0xF000) == 0) {
        goto finish;
    }

    if (buttons & 0xF000) {
        ((S_800B260C_1 *)arg0)->unk_10.s = 0;
        buttons = ((S_800B260C_0 *)base)->unk_10.u;
        if (buttons & 0x8000) {
            action = -5;
            goto apply;
        }
        if (buttons & 0x2000) {
            action = 5;
            goto apply;
        }
        if (buttons & 0x1000) {
            action = -1;
            goto apply;
        }
        if (buttons & 0x4000) {
            action = 1;
            goto apply;
        }
    } else {
        count = ((S_800B260C_1 *)arg0)->unk_10.s;
        if (count < 5) {
            ((S_800B260C_1 *)arg0)->unk_10.s = count + 1;
        } else {
            if (input & 0x8000) {
                action = -5;
                goto decrement;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (input & 0x2000) {
                action = 5;
                goto decrement;
            }
            input2 = ((S_800B260C_0 *)base)->unk_08;
            if (input2 & 0x1000) {
                action = -1;
                goto decrement;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (input2 & 0x4000) {
                action = 1;
            }
decrement:
            ((S_800B260C_1 *)arg0)->unk_10.u--;
        }
    }

apply:
    if (action != 0) {
        SD_Call(0x502);
        func_800B1F80(arg0, action);
    }

finish:
    func_800B1DCC(arg0);
}
