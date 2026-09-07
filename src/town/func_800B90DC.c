#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B683C_1 {
    u8 pad_00[0x98];
    void * unk_98;
} S_800B683C_1;   /* arg0 in func_800B683C */

typedef struct S_800B683C_2 {
    u8 pad_00[0x5C];
    void ** unk_5C;
} S_800B683C_2;   /* ((S_800B683C_1 *)arg0)->unk_98 in func_800B683C */




M2C_UNK func_800B6580();

typedef struct S_800B683C_0 {
    u8 pad_00[0x98];
    void * unk_98;
} S_800B683C_0;   /* arg0 in func_800B683C */

void func_800B683C(void *arg0) {
    s32 *temp_v0;
    s32 var_a1;

    var_a1 = 0x14;
    do {
        temp_v0 = *(s32 **)((var_a1 * 4) + ((S_800B683C_0 *)arg0)->unk_98);
        var_a1 += 1;
        *temp_v0 = 0;
    } while (var_a1 < 0x16);
    *((S_800B683C_2 *)(((S_800B683C_1 *)arg0)->unk_98))->unk_5C = arg0 + 0x18;
    func_800B6580(*((S_800B683C_2 *)(((S_800B683C_1 *)arg0)->unk_98))->unk_5C, 0);
}
