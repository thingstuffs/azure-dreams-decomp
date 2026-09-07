#include "common.h"
#include "m2c_compat.h"

typedef struct S_80018160_1 {
    u8 pad_00[0x278];
    M2C_UNK (*unk_278)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
} S_80018160_1;   /* D_80016000->unk_20 in func_80018160 */


typedef struct S_80018160_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80018160_0;   /* D_80016000 in func_80018160 */


extern S_80018160_0 *D_80016000;

void func_80018160(void) {
    ((S_80018160_1 *)(D_80016000->unk_20))->unk_278(1, 2, 0, 0x50);
}
