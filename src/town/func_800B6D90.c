#include "common.h"





#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80048FBC();
s32 func_80049004();
s32 func_800491CC();
extern s32 D_8002E5E8[];

typedef struct S_800B44F0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x10];
    s32 unk_5C;
} S_800B44F0_0;   /* arg0 in func_800B44F0 */

typedef struct S_800B44F0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800B44F0_1;   /* temp_v1 in func_800B44F0 */

s32 func_800B44F0(void *arg0, s32 arg1)
{
    s32 *temp_v1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;

    var_s1 = 0;
    temp_s2 = arg0 + 0x60;
    temp_v0 = func_80049004(temp_s2, arg1, 0xC);
    ((S_800B44F0_0 *)arg0)->unk_5C = temp_v0;
    if (temp_v0 != 0) {
        register s32 call_arg ASM_REG("$4") = temp_v0;   /* MATCH pin: load-bearing for the whole function shape */

        ASM_KEEP(call_arg);   /* MATCH pin: load-bearing for the whole function shape */
        temp_v1 = D_8002E5E8;
        ((S_800B44F0_0 *)arg0)->unk_40 = D_8002E5E8[0];
        ((S_800B44F0_0 *)arg0)->unk_44 = ((S_800B44F0_1 *)temp_v1)->unk_04;
        ((S_800B44F0_0 *)arg0)->unk_48 = ((S_800B44F0_1 *)temp_v1)->unk_08;
        func_800491CC(call_arg, arg0 + 0x40, 0x21);
        temp_v0_2 = func_80048FBC(temp_s2, 0xC);
        var_s1 = temp_v0_2 != 0;
        ((S_800B44F0_0 *)arg0)->unk_20 = temp_v0_2;
    }
    return var_s1;
}
