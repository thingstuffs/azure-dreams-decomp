#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_80054C58.c, etc.) */
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

/* Canonical "task/timer object" struct (see src/w_800552C8.c). */
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

extern S_800847D0 D_800847D0;
extern S_800848F8 D_800848F8;

extern void func_800552C8(void);
extern void func_8005AF74(s16 a0);
extern void func_8005AFF4(s16 a0);
extern void func_800550E8(void);
extern void func_8005B070(s16 a0);
extern void func_8005B16C(s16 a0);

/* Applies a status-flag transition for a status-effect code: 0x71 (full clear: if either the
   0x100 or 0x1000 activity bit is set, zeroes D_800848F8.field8, runs func_800552C8 and the two
   field22-keyed cleanup calls; unconditionally zeroes D_800848F8.field4, clears both activity
   bits and D_800847D0.flags2's bit 0x2, and re-triggers func_800550E8 if field26 is armed),
   0xE1 (activation edge: bit 0x100 -> 0x1000, calling func_8005B070 first), and 0xF1
   (deactivation edge: bit 0x1000 -> 0x100, calling func_8005B16C first). Any other code is a
   no-op. */
void func_800553D4(u8 code) {
    switch (code) {
    case 0x71:
        if (D_800847D0.flags1 & 0x1100) {
            D_800848F8.field8 = 0;
            func_800552C8();
            func_8005AF74(D_800847D0.field22);
            func_8005AFF4(D_800847D0.field22);
        }
        D_800848F8.field4 = 0;
        D_800847D0.flags1 &= ~0x100;
        D_800847D0.flags1 &= ~0x1000;
        D_800847D0.flags2 &= ~2;
        if (D_800847D0.field26 != -1) {
            func_800550E8();
        }
        break;
    case 0xE1:
        if (D_800847D0.flags1 & 0x100) {
            func_8005B070(D_800847D0.field22);
            D_800847D0.flags1 = (D_800847D0.flags1 & ~0x100) | 0x1000;
        }
        break;
    case 0xF1:
        if (D_800847D0.flags1 & 0x1000) {
            func_8005B16C(D_800847D0.field22);
            D_800847D0.flags1 = (D_800847D0.flags1 & ~0x1000) | 0x100;
        }
        break;
    }
}
