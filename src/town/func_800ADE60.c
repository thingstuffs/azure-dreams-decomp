#include "common.h"

typedef struct S_800AB5C0_0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800AB5C0_0;   /* arg0 in func_800AB5C0 */

typedef struct S_800AB5C0_1 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800AB5C0_1;   /* arg1 in func_800AB5C0 */



extern s32 func_800AAE98(void *);
extern void func_800AAFE0(void *, s32);
extern s32 func_800AB030(void *);
extern void func_800AB6EC(void);
extern u8 D_800AB408[];
extern u8 D_800AB708[];

void func_800AB5C0(S_800AB5C0_0 *arg0, S_800AB5C0_1 *arg1) {
    s16 buf[12];
    s32 offset;
    u16 timer;

    if (arg0->unk_90 < 100) {
        arg0->unk_50 = D_800AB708;
    }
    func_800AAFE0(buf, 4);
    offset = func_800AAE98(arg1);
    buf[5] -= offset + func_800AB030(arg0);
    timer = arg0->unk_6C - 1;
    arg0->unk_6C = timer;
    if ((s16)timer < 0) {
        arg1->unk_0E = arg1->unk_02.s = buf[1];
        arg1->unk_12 = arg1->unk_06.s = buf[3];
        arg1->unk_16 = arg1->unk_0A.s = buf[5];
        arg0->unk_50 = D_800AB408;
        arg0->unk_6C = 150;
        return;
    }
    arg1->unk_02.u = (arg1->unk_02.u + buf[1]) / 2;
    arg1->unk_06.u = (arg1->unk_06.u + buf[3]) / 2;
    arg1->unk_0A.u = (arg1->unk_0A.u + buf[5]) / 2;
}

/* MECHANISM: A 24-byte s16 stack object keeps the sampled coordinates at
   sp+0x12/+0x16/+0x1A; arg0/arg1 and the cross-call offset form s2/s1/s0.
   Chained copies load each coordinate once; the expired arm restores 150. */
