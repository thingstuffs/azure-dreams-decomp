#include "common.h"
#include "shared/sound_volume.h"

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

extern void func_8005A56C(s32 mode, s32 level_a, s32 level_b);

/* When status flag 0x400 is set: D_80084858's level, scaled by volume scale [2], goes to func_8005A56C (mode 0). */
void func_80054D64(void) {
    s16 level;
    s32 scaled;

    if (D_800847D0.flags1 & 0x400) {
        S_80084858 *task = &D_80084858;

        level = (task->field8 * volumeScale[2]) / 32767;
        scaled = level * task->field10;
        level = scaled / 128;
        func_8005A56C(0, level, level);
    }
}
