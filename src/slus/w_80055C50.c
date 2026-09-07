#include "common.h"

/* Clears availability bit (16+n) of D_800847D0.flags1 for channel n, notifying the
   channel-release path (func_8005AC68). If n==0 and status bit 0x100 is set, first
   fires a stop-note event (func_800553D4(0x71)) and resets field26 to -1. */
/* Canonical status-block struct at D_800847D0 (established elsewhere in the codebase:
   w_800540A8.c / w_80054C58.c / w_8005405C.c / w_800559B4.c / w_800552C8.c). */
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

extern void func_800553D4(s32 a0);
extern void func_8005AC68(s16 a0);

void func_80055C50(s16 a0) {
    s16 v0 = a0;
    S_800847D0 *p = &D_800847D0;
    if (p->flags1 & (0x10000 << v0)) {
        if (v0 == 0) {
            if (p->flags1 & 0x100) {
                func_800553D4(0x71);
                p->field26 = -1;
            }
        }
        func_8005AC68((s16) a0);
        D_800847D0.flags1 &= ~(0x10000 << ((s16) a0));
    }
}
