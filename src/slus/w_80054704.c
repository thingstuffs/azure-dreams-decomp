#include "common.h"

#include "common.h"

/* Canonical status block shared across the D_800847D0 family (established in
   w_80054E00.c / w_800540A8.c / w_80054C58.c / w_800559B4.c). */
typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u32 field8;
    /* 0x0C */ u32 fieldC;
    /* 0x10 */ u32 field10;
    /* 0x14 */ u32 field14;
    /* 0x18 */ u32 field18;
    /* 0x1C */ s16 field1C;
    /* 0x1E */ s16 field1E;
    /* 0x20 */ s16 field20;
    /* 0x22 */ s16 field22;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 field26;
    /* 0x28 */ u8 field28;
    /* 0x29 */ u8 pad29[7];
    /* 0x30 */ s8 field30;
    /* 0x31 */ s8 field31;
    /* 0x32 */ s8 field32;
    /* 0x33 */ s8 field33;
} S_800847D0;

extern S_800847D0 D_800847D0;

extern s32 func_8003F5AC(void);
extern void func_80054D64(void);
extern void func_80054E00(s32 arg0);
extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);

/* When subsystem bit 4 is set, clears flag 0x200 and commits or arms the countdown. */
void func_80054704(void) {
    if (func_8003F5AC() & 4) {
        D_800847D0.flags2 &= ~0x200;
        if (D_800847D0.field10 != 0) {
            func_80054E00(0x74);
            return;
        }
        if (!(D_800847D0.flags1 & 0x4000)) {
            D_800847D0.flags1 |= 0x400;
            func_80054D64();
            func_8005A4E8(0, 0, 1);
        }
    }
}
