#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80017E5C_1 {
    u8 pad_00[0x310];
    M2C_UNK (*unk_310)(M2C_UNK, M2C_UNK, M2C_UNK);
} S_80017E5C_1;   /* D_80016000->unk_20 in func_80017E5C */




extern Rec_D_80016000 *D_80016000;

/* Invoke the state callback with fixed parameters and return success. */
s32 func_80017E5C(void) {
    ((S_80017E5C_1 *)(D_80016000->unk_20))->unk_310(0x26, 0x200, 0x9000);
    return 1;
}
