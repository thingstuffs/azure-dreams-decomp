#include "common.h"

typedef struct S_8009567C_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009567C_0;   /* (u8 *)arg0 + temp_v1 in func_8009567C */

typedef struct S_8009567C_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8009567C_1;   /* (u8 *)arg0 + temp_v1 * 4 in func_8009567C */

typedef struct S_8009567C_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
} S_8009567C_2;   /* arg0 in func_8009567C */

typedef struct S_8009567C_3 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_8009567C_3;   /* temp_v0_2 in func_8009567C */



typedef struct {
    u8 pad_00[8];
    s32 field_08;
    u8 pad_0C[0xBC];
    s16 field_C8;
} SharedState;

extern SharedState D_80083160;
extern s16 D_800D0464;
extern s32 D_800D046C;

extern s16 func_80094BC8(s32, s16);
extern void func_8009574C();

s32 func_8009567C(void *arg0)
{
    s16 *var_a0;
    s16 temp_v0;
    s32 *var_a1;
    s32 temp_a3;
    s32 temp_v1;
    u8 temp_v1_2;
    s32 temp_t0;
    s32 var_a2;
    S_8009567C_3 *temp_v0_2;

    temp_v0 = func_80094BC8(D_80083160.field_08, D_80083160.field_C8);
    if (temp_v0 != -1) {
        var_a2 = 0;
        temp_a3 = ((temp_v0 + 0x100) / 0x200) & 7;
        temp_t0 = 1;
        var_a1 = &D_800D046C;
        var_a0 = &D_800D0464;
loop:
        if (temp_a3 == *var_a0) {
            temp_v1 = *var_a1;
            if (((S_8009567C_0 *)((u8 *)arg0 + temp_v1))->unk_3A != 0) {
                temp_v0_2 = ((S_8009567C_1 *)((u8 *)arg0 + temp_v1 * 4))->unk_1C;
                ((S_8009567C_2 *)arg0)->unk_18 = temp_v1;
                ((S_8009567C_2 *)arg0)->unk_10 = temp_v0_2;
                temp_v1_2 = temp_v0_2->unk_14;
                ASM_USE(temp_v0_2);   /* MATCH pin: load-bearing for the whole function shape */
                if (temp_v1_2 != temp_t0) {
                    func_8009574C(var_a0, var_a1, var_a2, temp_a3);
                    return 1;
                }
                return -1;
            }
        }
        var_a1++;
        var_a2++;
        var_a0++;
        if (var_a2 < 4) {
            goto loop;
        }
    }
    return 0;
}
