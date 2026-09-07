#include "common.h"

/* 8-byte "frame" element: a scalar and a pointer field */
typedef struct S_800489F4_Frame {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ void *unk4;
} S_800489F4_Frame;

/* object touched by this function; only the accessed fields are named */
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

/* Selects Frame table[a1][a2] via a 4-level pointer chain rooted at a0->unk28,
 * installs the frame pointer and its secondary pointer field into a0, and
 * updates a0's animation-state flags. */
void func_800489F4(S_800489F4_Obj *a0, s16 a1, s16 a2) {
    S_800489F4_Frame ***p2 = *a0->unk28;
    S_800489F4_Frame **p3 = *p2;
    S_800489F4_Frame *elemBase = p3[a1];
    S_800489F4_Frame *elem = &elemBase[a2];
    void *tmp;

    a0->unk0 = elem;
    tmp = elem->unk4;
    a0->unk4 = (u8)a2;
    a0->unk14 = (a0->unk14 & ~0x40) | 0x20;
    a0->unk8 = tmp;
}
