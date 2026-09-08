#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_80054C58.c,
   src/w_80055C50.c, src/w_8005440C.c, src/w_80054D64.c, src/w_800553D4.c, etc.):
   flags1@0x0, flags2@0x4, field8/fieldC/field10/field14/field18@0x8.. */
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
extern void func_80055D84(s16 param_0);

/* Reactivates the first locked channel and clears its lock flag. */
void func_80055CF4(void) {
    u32 channel;
    u32 channel_bit;
    u32 lock_bit;
    u32 lock_flags = D_800847D0.flags2 & 0xFF000000;

    for (channel = 0; channel < 4; channel++) {
        channel_bit = 0x1000000 << channel;
        lock_bit = channel_bit & 0xF000000;
        if (lock_flags & lock_bit) {
            func_80055D84((s16) channel);
            D_800847D0.flags2 &= ~lock_bit;
            break;
        }
    }
}
