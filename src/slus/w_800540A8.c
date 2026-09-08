#include "common.h"

/* callee: task/timer-like initializer, already matched in src/code.c */
typedef struct {
    char pad0[4];      /* 0x0 */
    int field4;        /* 0x4 */
    char pad8[4];      /* 0x8 */
    int fieldC;        /* 0xC */
    short field10;     /* 0x10 */
    char pad12[4];     /* 0x12 */
    short field16;     /* 0x16 */
    short field18;     /* 0x18 */
} D_80055990_Struct;

extern void func_80055990(D_80055990_Struct *a0);
extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);

extern D_80055990_Struct D_80084858;

/* Sibling struct for D_800847D0: fields cleared here are a subset of a larger
   object; layout inferred purely from the offsets this function touches. */
typedef struct {
    char pad0[8];             /* 0x0 */
    s32 field8;                /* 0x8 */
    s32 fieldC;                 /* 0xC */
    s32 field10;                 /* 0x10 */
    s32 field14;                 /* 0x14 */
    s32 field18;                 /* 0x18 */
    char pad1C[0x30 - 0x1C];   /* 0x1C */
    s8 field30;                 /* 0x30 */
    s8 field31;                 /* 0x31 */
    s8 field32;                 /* 0x32 */
    s8 field33;                 /* 0x33 */
} S_800847D0;

extern S_800847D0 D_800847D0;

/* Resets the audio command state and task object, then clears playback status fields. */
void func_800540A8(void) {
    func_8005A4E8(0, 0, 0);
    func_80055990(&D_80084858);

    D_800847D0.field8 = 0;
    D_800847D0.fieldC = 0;
    D_800847D0.field30 = 0;
    D_800847D0.field32 = 0;
    D_800847D0.field10 = 0;
    D_800847D0.field14 = 0;
    D_800847D0.field31 = 0;
    D_800847D0.field33 = 0;
    D_800847D0.field18 = 0;
}
