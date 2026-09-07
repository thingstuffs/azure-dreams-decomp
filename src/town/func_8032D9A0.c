#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_800181A0_1 {
    u8 pad_00[0x278];
    M2C_UNK (*unk_278)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
} S_800181A0_1;   /* D_80016000->unk_20 in func_800181A0 */




extern Rec_D_80016000 *D_80016000;

void func_800181A0(void) {
    ((S_800181A0_1 *)(D_80016000->unk_20))->unk_278(1, 1, 0, 0x1E);
}
