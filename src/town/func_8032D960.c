#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80018160_1 {
    u8 pad_00[0x278];
    M2C_UNK (*unk_278)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
} S_80018160_1;   /* D_80016000->unk_20 in func_80018160 */




extern Rec_D_80016000 *D_80016000;

/* Invoke the callback at offset 0x278 with settings (1, 2, 0, 0x50). */
void func_80018160(void) {
    ((S_80018160_1 *)(D_80016000->unk_20))->unk_278(1, 2, 0, 0x50);
}
