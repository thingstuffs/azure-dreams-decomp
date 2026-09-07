#include "common.h"

typedef struct S_8005A4E8 {
    s32 type;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} S_8005A4E8;

extern void func_8005EDA0(S_8005A4E8 *s);

/* Builds a stack-local tagged struct from two boolean bytes (a0,a1) selecting
 * one of four type codes, stores the byte a2 into a type-specific field, and
 * passes the struct's address to func_8005EDA0. */
void func_8005A4E8(u8 a0, u8 a1, u8 a2) {
    S_8005A4E8 s;
    if (a0 == 0) {
        if (a1 == 0) {
            s.type = 0x200;
            s.unk18 = a2;
        } else {
            s.type = 0x100;
            s.unk14 = a2;
        }
    } else {
        if (a1 == 0) {
            s.type = 0x2000;
            s.unk24 = a2;
        } else {
            s.type = 0x1000;
            s.unk20 = a2;
        }
    }
    func_8005EDA0(&s);
}
