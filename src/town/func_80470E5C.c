#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017E5C_1 {
    u8 pad_00[0x310];
    M2C_UNK (*unk_310)(M2C_UNK, M2C_UNK, M2C_UNK);
} S_80017E5C_1;   /* D_80016000->unk_20 in func_80017E5C */


typedef struct S_80017E5C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80017E5C_0;   /* D_80016000 in func_80017E5C */


extern S_80017E5C_0 *D_80016000;

s32 func_80017E5C(void) {
    ((S_80017E5C_1 *)(D_80016000->unk_20))->unk_310(0x26, 0x200, 0x9000);
    return 1;
}
