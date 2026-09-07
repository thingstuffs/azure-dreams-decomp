#include "common.h"
#include "m2c_compat.h"

typedef struct S_800181A0_1 {
    u8 pad_00[0x278];
    M2C_UNK (*unk_278)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
} S_800181A0_1;   /* D_80016000->unk_20 in func_800181A0 */


typedef struct S_800181A0_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800181A0_0;   /* D_80016000 in func_800181A0 */


extern S_800181A0_0 *D_80016000;

void func_800181A0(void) {
    ((S_800181A0_1 *)(D_80016000->unk_20))->unk_278(1, 1, 0, 0x1E);
}
