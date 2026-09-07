#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80100E40;

typedef struct S_800AB014_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800AB014_0;   /* arg0 in func_800AB014 */

typedef struct S_800AB014_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800AB014_1;   /* p in func_800AB014 */

void func_800AB014(S_800AB014_0 *arg0, s32 arg1) {
    s8 *base;
    s8 *p;

    base = (s8 *) &D_80100E40;
    p = base + (arg1 * 8);
    arg0->unk_72 = (u16) ((S_800AB014_1 *)p)->unk_06;
}
