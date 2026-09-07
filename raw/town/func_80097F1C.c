#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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
    void *temp_v0_2;

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
            if (FIELD((u8 *)arg0 + temp_v1, u8, 0x3A) != 0) {
                temp_v0_2 = FIELD((u8 *)arg0 + temp_v1 * 4, void *, 0x1C);
                FIELD(arg0, s32, 0x18) = temp_v1;
                FIELD(arg0, void *, 0x10) = temp_v0_2;
                temp_v1_2 = FIELD(temp_v0_2, u8, 0x14);
                ASM_USE(temp_v0_2);
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
