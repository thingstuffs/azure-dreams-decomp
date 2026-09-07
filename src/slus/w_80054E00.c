#include "common.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c). field1C added here (previously an unnamed
   2-byte pad window) since this function reads it as a signed 16-bit value. */
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

/* Canonical task/timer object struct (established in w_800559B4.c / w_800540A8.c
   / w_80054C58.c). */
typedef struct S_80084858 {
    /* 0x00 */ void (*field0)(void);
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ s16 fieldA;
    /* 0x0C */ s32 fieldC;
    /* 0x10 */ s16 field10;
    /* 0x12 */ s16 field12;
    /* 0x14 */ s16 field14;
    /* 0x16 */ s16 field16;
    /* 0x18 */ s16 field18;
} S_80084858;

/* Opaque scalar flag; only its address is taken (never dereferenced beyond a
   single s32 write). Padded >8 bytes to force %hi/%lo addressing (matches the
   target's lui+addiu/sw sequence rather than a $gp_rel store). */
typedef struct S_80084904 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084904;

/* Same shape/reasoning as S_80084904. */
typedef struct S_80084864 {
    /* 0x00 */ s32 v;
    /* 0x04 */ u8 pad4[8];
} S_80084864;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern S_80084904 D_80084904;
extern S_80084864 D_80084864;

extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);
extern s32 func_80053D64(void);
extern int func_80054AF0(int arg0);
extern void func_80054C58(void);
extern void func_80054CD4(void);

/* Message/event dispatcher for a subsystem keyed by a byte opcode
   (arg0 & 0xFF): 0xE4 = query/arm a countdown against a CD-position-derived
   value; 0x74 = commit a countdown (rotating pending fields into active ones
   via func_80054C58/func_80054CD4) once armed; 0xF4 = cancel an armed
   countdown (same commit path). */
void func_80054E00(s32 arg0) {
    s32 op = arg0 & 0xFF;

    if (op == 0xE4)
        goto case_E4;

    if (op < 0xE5) {
        if (op == 0x74)
            goto case_74;
        return;
    }

    if (op == 0xF4)
        goto case_F4;
    return;

case_74:
    func_8005A4E8(0, 0, 0);
    func_8003E4FC(9, 0, 0);
    D_800847D0.flags1 &= ~0x400;
    if (D_800847D0.field18 == 0) {
        D_80084904.v = 1;
        D_80084858.field4 = 0;
        if (D_800847D0.field10 != 0) {
            s16 r = (s16)func_80054AF0(D_800847D0.field1C);
            D_80084858.field8 = r;
            D_80084858.fieldA = r;
            goto tail;
        }
    }
    return;

case_E4:
    if (D_800847D0.flags2 & 0x200) {
        func_8003E4FC(9, 0, 0);
        return;
    }
    if (D_800847D0.flags1 & 0x400) {
        u32 r = (u32)func_80053D64();
        D_800847D0.field18 = r;
        if (D_800847D0.field8 >= r) {
            D_800847D0.field18 = D_800847D0.field8;
        }
        D_80084864.v = 2;
        D_800847D0.field10 = D_800847D0.field18;
        D_800847D0.field14 = D_800847D0.fieldC;
        D_800847D0.field31 = D_800847D0.field30;
        D_800847D0.field33 = D_800847D0.field32;
        D_800847D0.flags1 |= 0x4000;
    }
    return;

case_F4:
    if (D_800847D0.flags1 & 0x4000) {
        D_800847D0.field18 = 0;
        goto tail;
    }
    return;

tail:
    func_80054C58();
    func_80054CD4();
}
