#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002506C_0 {
    void * unk_00;
} S_8002506C_0;   /* arg0 in func_8002506C; pointer addresses record offset 0x14 */

typedef struct S_8002506C_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8002506C_1;   /* temp_a0 in func_8002506C */

typedef struct S_8002506C_2 {
    u16 unk_00;
    u16 unk_02;
} S_8002506C_2;   /* temp_v1 in func_8002506C */


extern u8 D_80024004[24];

void func_8002506C(void *arg0, s32 arg1) {
    u16 sp[12];
    s32 var_v0;
    S_8002506C_1 *temp_a0;
    S_8002506C_2 *temp_v1;

    __builtin_memcpy(sp, D_80024004, 24);
    if ((u32)(arg1 & 0xFFFF) >= 6U) {
        arg1 = 0;
    }
    var_v0 = arg1 << 0x10;
    temp_v1 = (u8 *)sp + (var_v0 >> 0xE);
    temp_a0 = ((S_8002506C_0 *)((u8 *)arg0 - 0x14))->unk_00;
    temp_a0->unk_1C = (u16)temp_v1->unk_00;
    temp_a0->unk_1E = (u16)temp_v1->unk_02;
}
