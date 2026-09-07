#include "common.h"
#include "m2c_compat.h"

s32 func_800AB464();                                /* extern */
extern M2C_UNK D_800D4494;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D491C_0;   /* arg0 in func_800D491C */

void func_800D491C(S_800D491C_0 *arg0) {
    if (func_800AB464() > 0) {
        arg0->unk_8C = &D_800D4494;
    }
}
