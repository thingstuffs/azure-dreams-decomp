#include "common.h"

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

/* Releases an available channel, stopping channel zero's note when its status requires it. */
void func_80055C50(s16 channel) {
    s16 channel_index = channel;
    S_800847D0 *status = &D_800847D0;
    if (status->flags1 & (0x10000 << channel_index)) {
        if (channel_index == 0) {
            if (status->flags1 & 0x100) {
                func_800553D4(0x71);
                status->field26 = -1;
            }
        }
        func_8005AC68((s16) channel);
        D_800847D0.flags1 &= ~(0x10000 << ((s16) channel));
    }
}
