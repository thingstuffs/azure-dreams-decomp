#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A130C_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A130C_0;   /* arg0 in func_800A130C */

typedef struct S_800A130C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A130C_1;   /* arg1 in func_800A130C */

/* Copies three spaced halfwords into consecutive destination fields. */
void func_800A130C(S_800A130C_0 *dst, S_800A130C_1 *src) {
    dst->unk_00 = (u16) src->unk_02;
    dst->unk_02 = (u16) src->unk_06;
    dst->unk_04 = (u16) src->unk_0A;
}
