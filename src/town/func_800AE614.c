#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800ABC00(void *, s16);              /* extern */

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    u16 z;
    s32 a;
    s32 b;
    s16 unk14;
    s16 c;
} StackRecord;

typedef struct S_800ABD74_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800ABD74_0;   /* base in func_800ABD74 */

void func_800ABD74(void *arg0) {
    S_800ABD74_0 *base;
    StackRecord sp10;
    s32 var_s0;
    register s32 temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_s4;
    s32 var_s1;

    base = arg0;
    temp_s2 = (rand() & 7) | 4;
    temp_s4 = 0x1000 / temp_s2;
    var_s1 = 0;
    var_s0 = rand();
    ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    sp10.z = base->unk_0A;
    sp10.c = -4;
    if (temp_s2 != 0) {
        do {
            var_s1 += 1;
            sp10.x = (base->unk_02 + (rand() & 0x1F)) - 0x10;
            sp10.y = (base->unk_06 + (rand() & 0x1F)) - 0x10;
            sp10.a = func_80064584(var_s0) << 5;
            sp10.b = func_800644B8(var_s0) << 5;
            func_800ABC00(&sp10, var_s0);
            var_s0 += temp_s4;
        } while (var_s1 < temp_s2);
    }
}

/* MECHANISM: One 24-byte stack record reproduces the overlapping sp+0x10 fields and 0x40 frame.
   The base pin holds arg0 in s3; the s2 pin/early keeps retain the otherwise-folded beqz.
   The s16 callee ABI and load-before--4-store order close the tail and its delay slot. */
