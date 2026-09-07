#include "common.h"
#include "m2c_compat.h"

void *func_8003FE78();   /* extern */
extern M2C_UNK D_800A24FC;
extern M2C_UNK D_80100BF0;

typedef struct S_800A24C4_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800A24C4_0;   /* temp_v0 in func_800A24C4 */

void func_800A24C4(void) {
    S_800A24C4_0 *temp_v0;

    temp_v0 = func_8003FE78(0x136, &D_80100BF0, 0x49);
    temp_v0->unk_10 = &D_800A24FC;
    temp_v0->unk_2C = 0;
}
