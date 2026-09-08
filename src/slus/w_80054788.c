#include "common.h"

/* Canonical status-block struct (established in w_800540A8.c / w_80054C58.c /
   w_800559B4.c / w_8005440C.c / w_80054E00.c). This function only reads
   flags1 (offset 0x0). */
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

/* Canonical task/timer object struct (established in w_800559B4.c /
   w_800540A8.c / w_80054C58.c / w_80054E00.c). Only its address is taken by
   this function, no fields accessed here. */
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

/* Canonical task/event object struct (established in w_8005440C.c). Only its
   address is taken by this function, no fields accessed here. */
typedef struct S_800848F8 {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ u8 pad0A[0x36];
} S_800848F8;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern S_800848F8 D_800848F8;

extern void func_8005497C(u16 a0);
extern void func_800549FC(u16 a0);
extern void func_800553D4(u8 a0);
extern void func_80054104(void);
extern void func_80054E00(s32 a0);
extern void func_80054A7C(u8 a0);
extern void func_80054F9C(u32 a0, void *a1);

/* MIDI-style channel-event dispatcher: switches on the high nibble of the
   packed status byte `arg0`. 0x10/0x20 forward the full 16-bit value to
   dedicated handlers; 0x70 fires up to three independent event handlers
   gated by bits 0/1/2 of arg0; 0xB0/0xC0/0xD0 share a block that (if bit0
   set and flags1 has 0x100 set and 0x1000 clear) relays a masked event to
   D_800848F8 via func_80054F9C, and (if bit2 set and flags1 has 0x400 set
   and 0x4000 clear) relays another masked event to D_80084858; 0xE0/0xF0
   fire up to two handlers gated by bits 0/2; every other nibble falls
   through to a generic default handler (func_80054A7C). */
void func_80054788(s32 arg0) {
    s32 a = arg0;
    register s32 b ASM_REG("$17") = a;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    switch (a & 0xF0) {
    case 0x10:
        func_8005497C(b & 0xFFFF);
        break;
    case 0x20:
        func_800549FC(b & 0xFFFF);
        break;
    case 0x70:
        if (a & 1) func_800553D4(0x71);
        if (a & 2) func_80054104();
        if (a & 4) func_80054E00(0x74);
        break;
    case 0xE0:
        if (a & 1) func_800553D4(0xE1);
        if (a & 4) func_80054E00(0xE4);
        break;
    case 0xF0:
        if (a & 1) func_800553D4(0xF1);
        if (a & 4) func_80054E00(0xF4);
        break;
    case 0xB0:
    case 0xC0:
    case 0xD0:
        if (b & 1) {
            if (D_800847D0.flags1 & 0x100) {
                if (!(D_800847D0.flags1 & 0x1000)) {
                    func_80054F9C(b & 0xFFF1, &D_800848F8);
                }
            }
        }
        if (b & 4) {
            if (D_800847D0.flags1 & 0x400) {
                if (!(D_800847D0.flags1 & 0x4000)) {
                    func_80054F9C(b & 0xFFF4, &D_80084858);
                }
            }
        }
        break;
    default:
        func_80054A7C(b & 0xFF);
        break;
    }
}
