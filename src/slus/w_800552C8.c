#include "common.h"

/* Canonical "task/timer object" struct shared with func_80055990's own D_80055990_Struct
   (src/code.c) and w_800540A8.c's D_80055990_Struct / w_80054C58.c's S_80084858: field0 is
   a function pointer, followed by s16 field8/fieldA, s32 fieldC, then more s16 fields. */
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

/* Canonical status-block struct at D_800847D0, established in w_800540A8.c / w_80054C58.c /
   w_8005405C.c / w_800559B4.c: flags1@0x0, flags2@0x4, field8/fieldC/field10/field14@0x8/0xC/
   0x10/0x14, field18-33 across the tail. */
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
extern S_800848F8 D_800848F8;
extern s16 D_80084808[8];

extern s32 func_80055750(s16 arg0);
extern void func_8005B27C(s16 a0, s32 a1, s32 a2);

/* Scale and clamp the output value when enabled, then apply it to both channels. */
void func_800552C8(void)
{
    s32 scale_product;
    s32 scaled_value;
    s16 channel_value;

    if (D_800847D0.flags1 & 0x100) {
        scale_product = D_800848F8.field8 * D_80084808[1];
        scaled_value = (s16) (scale_product / 32767);
        scaled_value = scaled_value * D_800848F8.field10;
        channel_value = func_80055750((s16) (scaled_value / 128));
        func_8005B27C(D_800847D0.field22, channel_value, channel_value);
    }
}
