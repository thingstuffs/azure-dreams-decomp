#include "common.h"

/* Canonical status block shared across the D_800847D0 family (w_800540A8.c,
   w_80054C58.c, w_8005405C.c, w_800559B4.c). Only flags1 is touched here. */
typedef struct S_800847D0 {
    u32 flags1;   /* 0x00 */
    u32 flags2;   /* 0x04 */
    u32 field8;   /* 0x08 */
    u32 fieldC;   /* 0x0C */
    u32 field10;  /* 0x10 */
    u32 field14;  /* 0x14 */
    u32 field18;  /* 0x18 */
    u8 pad1C[2];  /* 0x1C */
    s16 field1E;  /* 0x1E */
    s16 field20;  /* 0x20 */
    s16 field22;  /* 0x22 */
    u8 pad24[2];  /* 0x24 */
    s16 field26;  /* 0x26 */
    u8 field28;   /* 0x28 */
    u8 pad29[7];  /* 0x29 */
    s8 field30;   /* 0x30 */
    s8 field31;   /* 0x31 */
    s8 field32;   /* 0x32 */
    s8 field33;   /* 0x33 */
} S_800847D0;

/* Canonical "task/timer object" struct established in w_800559B4.c. field0 is a
   callback pointer (set to func_80054D64 there); field8/field10 are the two
   s16 fields this function reads. */
typedef struct S_80084858 {
    void (*field0)(void); /* 0x00 */
    s32 field4;            /* 0x04 */
    s16 field8;              /* 0x08 */
    s16 fieldA;                /* 0x0A */
    s32 fieldC;                /* 0x0C */
    s16 field10;                /* 0x10 */
    s16 field12;                  /* 0x12 */
    s16 field14;                    /* 0x14 */
    s16 field16;                      /* 0x16 */
    s16 field18;                        /* 0x18 */
} S_80084858;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern s16 D_8008480C[8];

extern void func_8005A56C(s32 arg0, s32 arg1, s32 arg2);

/* If status flag 0x400 is set, computes a pitch-bend value from D_80084858's
   field8/field10 scaling factors and D_8008480C[0] (a 0..32767-scaled
   percentage), then dispatches it as an SPU pitch-bend command via
   func_8005A56C (mode 0, same value on both channels). */
void func_80054D64(void) {
    s16 pitch;
    s32 tmp;

    if (D_800847D0.flags1 & 0x400) {
        S_80084858 *p = &D_80084858;

        pitch = (p->field8 * D_8008480C[0]) / 32767;
        tmp = pitch * p->field10;
        pitch = tmp / 128;
        func_8005A56C(0, pitch, pitch);
    }
}
