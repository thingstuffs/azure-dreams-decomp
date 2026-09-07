#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008F50C_0 {
    u8 pad_00[0x37];
    s8 unk_37;
} S_8008F50C_0;   /* arg0 in func_8008F50C */

typedef struct S_8008F50C_1 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8008F50C_1;   /* arg1 in func_8008F50C */

void func_8008F50C(S_8008F50C_0 *arg0, S_8008F50C_1 *arg1, s32 arg2) {
    arg0->unk_37 = 1;
    arg1->unk_00 = arg2;
    arg1->unk_0C = 0;
}
