#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036154_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036154_1;   /* arg0 in func_80036154 */

typedef struct S_80036154_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x71];
    s8 unk_85;
} S_80036154_2;   /* ((S_80036154_1 *)arg0)->unk_74 in func_80036154 */


typedef struct S_80036154_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    void * unk_74;
} S_80036154_0;   /* arg0 in func_80036154 */


M2C_UNK func_80036988();              /* extern */
extern M2C_UNK func_80036210;
extern M2C_UNK func_800362D0;
extern M2C_UNK func_800364EC;
extern M2C_UNK func_8003666C;
extern M2C_UNK func_800368D0;
extern M2C_UNK func_80038478;
extern M2C_UNK func_80038588;
extern M2C_UNK func_800385E8;
extern M2C_UNK func_80038648;
extern M2C_UNK func_80038A00;

void func_80036154(void *arg0) {
    M2C_UNK *var_v0;
    s32 temp_v1;

    temp_v1 = ((S_80036154_2 *)(((S_80036154_1 *)arg0)->unk_74))->unk_10;
    if (temp_v1 == &func_80038478) {
        var_v0 = &func_80036210;
        goto block_10;
    }
    if (temp_v1 == &func_80038588) {
        var_v0 = &func_800362D0;
        goto block_10;
    }
    if (temp_v1 == &func_800385E8) {
        var_v0 = &func_800364EC;
        goto block_10;
    }
    if (temp_v1 == &func_80038648) {
        var_v0 = &func_8003666C;
        goto block_10;
    }
    if (temp_v1 == &func_80038A00) {
        var_v0 = &func_800368D0;
block_10:
        ((S_80036154_0 *)arg0)->unk_68 = var_v0;
    }
    func_80036988(arg0 + 0xC, ((S_80036154_0 *)arg0)->unk_74);
    ((S_80036154_2 *)(((S_80036154_1 *)arg0)->unk_74))->unk_85 = 1;
}
