#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
M2C_UNK func_80170B50();
M2C_UNK func_80173C30();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u16 D_8008378A;
extern M2C_UNK D_8017112C;
extern M2C_UNK D_80171514;
extern M2C_UNK D_80173E8C;
extern void *D_80174710;

typedef struct S_80170F84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80170F84_0;   /* temp_v0 in func_80170F84 */

typedef struct S_80170F84_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x6C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_80170F84_1;   /* var_s4 in func_80170F84 */

typedef struct S_80170F84_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80170F84_2;   /* temp_s1 in func_80170F84 */

typedef struct S_80170F84_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80170F84_3;   /* temp_s0 in func_80170F84 */

void *func_80170F84(s16 arg0, s32 arg1, s16 arg2, u16 arg3) {
    S_80170F84_1 *var_s4 = NULL;
    s16 saved_arg1;
    s16 saved_arg3;
    s16 saved_arg2;
    u16 temp_s2;
    u16 temp_s3;
    S_80170F84_3 *temp_s0;
    S_80170F84_2 *temp_s1;
    void *temp_v0;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s4 = temp_v0 + 0x20;
        D_80174710 = temp_v0;
        ((S_80170F84_0 *)temp_v0)->unk_10 = &D_8017112C;
        var_s4->unk_13 = 0x37;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = ((S_80170F84_0 *)temp_v0)->unk_08;
        temp_s1->unk_0A = saved_arg3;
        temp_s0 = ((S_80170F84_0 *)temp_v0)->unk_0C;
        temp_s0->unk_24 = saved_arg1;
        temp_s0->unk_25 = saved_arg2;
        temp_s0->unk_2C = &D_80173E8C;
        var_s4->unk_9E = 0;
        func_800A9C18(temp_v0, temp_s1, temp_s0, arg0);
        var_s4->unk_9A = 0xFF;
        var_s4->unk_9C = -1;
        var_s4->unk_8C = &D_80171514;
        var_s4->unk_1C = (s32) (var_s4->unk_1C | 0x40000);
        temp_s0->unk_10 = 0x20;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        func_800AA36C(var_s4, temp_s1, temp_s0, var_s4);
        temp_s1->unk_0A = (u16) D_8008378A;
        temp_s1->unk_16 = (s16) (temp_s1->unk_0A - 0x20);
        temp_s1->unk_0A = (u16) (temp_s1->unk_0A - 0x190);
        temp_s2 = temp_s0->unk_1C;
        temp_s3 = temp_s0->unk_1E;
        temp_s0->unk_1C = 0U;
        temp_s0->unk_1E = 0U;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x80);
        func_80170B50(var_s4, temp_s1, temp_s0, 1);
        func_80170B50(var_s4, temp_s1, temp_s0, 2);
        temp_s0->unk_1C = temp_s2;
        temp_s0->unk_1E = temp_s3;
        func_80173C30();
    }
    return var_s4;
}
