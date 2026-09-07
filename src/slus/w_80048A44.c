#include "common.h"

/* Selects a frame via func_800489F4, dispatches via func_80048998, then divides the
 * newly-selected frame's leading u16 by the global divisor D_80080A84, storing the
 * quotient into obj->unk5 and clearing bits 0x6000 of obj->unk14. */
/* Frame element pointed to by S_80048A44_Obj.unk0; only the first field (a u16) is read here */
typedef struct S_80048A44_Frame {
    /* 0x0 */ u16 unk0;
} S_80048A44_Frame;

/* object touched by this function; only the accessed fields are named */
typedef struct S_80048A44_Obj {
    /* 0x00 */ S_80048A44_Frame *unk0;
    /* 0x04 */ u8 pad04;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 pad06[0x14 - 0x06];
    /* 0x14 */ u16 unk14;
} S_80048A44_Obj;

/* callee's exact type, per S_800489F4_Obj */
typedef struct S_800489F4_Frame {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ void *unk4;
} S_800489F4_Frame;

typedef struct S_800489F4_Obj {
    /* 0x00 */ S_800489F4_Frame *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad05[3];
    /* 0x08 */ void *unk8;
    /* 0x0C */ u8 pad0C[8];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[0x28 - 0x16];
    /* 0x28 */ S_800489F4_Frame ****unk28;
} S_800489F4_Obj;

/* callee's exact type, per S_80083110 */
typedef struct S_80083110 {
    u8 pad0[8];
    s32 field_8;
    u8 pad1[0x28 - 0xC];
    s32 field_28;
} S_80083110;

extern void func_800489F4(S_800489F4_Obj *a0, s16 a1, s16 a2);
extern void func_80048998(S_80083110 *a0, s32 a1);

/* D_80080A84 is addressed via %hi/%lo (not $gp-relative) in retail, so it must be
 * declared with size > 8 bytes to steer gcc away from small-data addressing. */
extern u8 D_80080A84[16];

void func_80048A44(S_80048A44_Obj *a0, s16 a1, s16 a2, s32 a3) {
    u16 v1;
    u8 divisor;

    func_800489F4((S_800489F4_Obj *)a0, a1, a2);
    func_80048998((S_80083110 *)a0, a3);

    v1 = a0->unk0->unk0;
    divisor = D_80080A84[0];
    a0->unk14 = a0->unk14 & 0x9FFF;
    a0->unk5 = (u8)((s32)v1 / (s32)divisor);
}
