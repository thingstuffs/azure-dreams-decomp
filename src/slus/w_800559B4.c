#include "common.h"

/* Canonical "task/timer object" struct shared with func_80055990's own D_80055990_Struct
   (src/code.c) and w_800540A8.c's D_80055990_Struct / w_80054C58.c's S_80084858: field0 is
   revealed here as a function pointer (this function stores a callback address into it),
   and the two 4-byte pad windows are each a pair of s16 fields. */
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

/* Same layout as S_80084858 (D_80055990_Struct family), independently named per its own
   global address per convention. */
typedef struct S_800848F8 {
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
} S_800848F8;

/* Extends the S_800847D0 view already established in w_800540A8.c / w_80054C58.c /
   w_8005405C.c (flags1@0x0, flags2@0x4, field8/fieldC/field10/field14@0x8/0xC/0x10/0x14,
   field30..33@0x30..0x33) with the additional fields this function touches in the
   0x18-0x29 window. */
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

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern S_800848F8 D_800848F8;
extern s16 D_80084808[8];
extern s32 D_80084850;

extern void func_80055990(void *a0);
extern void func_800552C8(void);
extern void func_80054D64(void);

/* Global init routine: clears/reinitializes the D_800847D0 status block, saturates the
   D_80084808 short array to 0x7FFF, zeroes D_80084850, initializes the two task/timer
   objects D_800848F8 and D_80084858 (via func_80055990), then installs their callback
   function pointers (func_800552C8 / func_80054D64) and remaining constant fields. */
void func_800559B4(void) {
    D_800847D0.flags1 = 0;
    D_800847D0.flags2 = 0;
    D_800847D0.flags1 = 0x10;
    D_800847D0.field1E = 0x5A;
    D_800847D0.field26 = -1;

    D_800847D0.field8 = 0;
    D_800847D0.fieldC = 0;
    D_800847D0.field30 = 0;
    D_800847D0.field32 = 0;
    D_800847D0.field10 = 0;
    D_800847D0.field14 = 0;
    D_800847D0.field31 = 0;
    D_800847D0.field33 = 0;
    D_800847D0.field18 = 0;
    D_800847D0.field22 = 0;
    D_800847D0.field20 = 0;

    D_80084808[0] = 0x7FFF;
    D_80084808[1] = 0x7FFF;
    D_80084808[2] = 0x7FFF;

    D_80084850 = 0;
    func_80055990(&D_800848F8);

    func_80055990(&D_80084858);

    D_800848F8.field0 = func_800552C8;
    D_800848F8.field8 = 0x64;
    D_800848F8.fieldA = 0x64;
    D_800848F8.field12 = 0x50;
    D_800848F8.field14 = 2;

    D_80084858.field0 = func_80054D64;
    D_80084858.field8 = 0x7F;
    D_80084858.fieldA = 0x7F;
    D_80084858.field14 = 0x14;
    D_80084858.field12 = 0;

    D_800847D0.field28 = 0xC8;
}
