#include "common.h"
#include "m2c_compat.h"

typedef struct S_8059E664_1 {
    u8 pad_00[0x220];
    M2C_UNK (*unk_220)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
} S_8059E664_1;   /* D_80016000->unk_20 in func_8059E664 */


typedef struct S_8059E664_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8059E664_0;   /* D_80016000 in func_8059E664 */


extern S_8059E664_0 *D_80016000;

void func_8059E664(void) {
    ((S_8059E664_1 *)(D_80016000->unk_20))->unk_220(2, 0xD, 0, 0);
}
