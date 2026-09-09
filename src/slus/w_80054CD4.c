#include "common.h"

/* Canonical status-block struct shared across the D_800847D0 family (see
   w_800552C8.c, w_80054C58.c, w_800540A8.c, w_80054E00.c). field2C/field2D
   are added here (previously unnamed pad bytes) since this function is the
   one that reads/writes them directly. */
typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u32 field8;
    /* 0x0C */ u32 fieldC;
    /* 0x10 */ u32 field10;
    /* 0x14 */ u32 field14;
    /* 0x18 */ u32 field18;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ s16 field1E;
    /* 0x20 */ s16 field20;
    /* 0x22 */ s16 field22;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 field26;
    /* 0x28 */ u8 field28;
    /* 0x29 */ u8 pad29[3];
    /* 0x2C */ u8 field2C;
    /* 0x2D */ u8 field2D;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s8 field30;
    /* 0x31 */ s8 field31;
    /* 0x32 */ s8 field32;
    /* 0x33 */ s8 field33;
} S_800847D0;

/* Opaque scalar flag; only its value is ever stored (never dereferenced
   beyond a single s32 write elsewhere). Padded >8 bytes to force %hi/%lo
   addressing (matches src/w_80054E00.c's S_80084904). */
typedef struct S_80084904 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084904;

extern S_800847D0 D_800847D0;
extern S_80084904 D_80084904;

extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);
extern void func_8005A56C(s32 a0, s32 a1, s32 a2);
extern s32 Control_CD(s32 a0, void *a1, void *a2);

/* Enters mode 2, activates pending status fields, resets subsystems, and registers status callbacks. */
void func_80054CD4(void) {
    S_800847D0 *status;
    u8 pending_2c;
    u8 pending_2d;

    D_80084904.v = 2;

    status = &D_800847D0;
    pending_2c = status->field32;
    pending_2d = status->field30;

    status->field2C = pending_2c;
    status->field2D = pending_2d;
    status->flags2 |= 0x200;

    func_8005A4E8(0, 0, 0);
    func_8005A56C(0, 0, 0);
    Control_CD(0xE, 0, &status->field28);
    Control_CD(0xD, (void *)(s32) status->field8, &status->field2C);
}
