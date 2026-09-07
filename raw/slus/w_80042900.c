#include "common.h"

#include "common.h"

typedef struct {
    s8 type;
    s8 value;
} S_80042900_Effect;

typedef struct {
    u8 pad0[0x14];
    s32 field_0x14;
    u8 pad1[(0x28 - 0x14) - 4];
    u8 field_0x28;
    u8 pad2[(0x2C - 0x28) - 1];
    S_80042900_Effect effects[4];
} S_80042900;

s32 func_80042900(S_80042900 *a0, s32 a1)
{
    register s32 key ASM_REG("$5") = a1;
    register s32 orig ASM_REG("$7") = a1;
    register u8 *effect_base ASM_REG("$3") = (u8 *)a0 + 6;
    s32 i;

    key = (u32)key << 24;
    key >>= 24;
    if (key != 0) {
        for (i = 3; i >= 0; i--, effect_base -= 2) {
            if (*(s8 *)(effect_base + 0x2C) == key) {
                s32 value = *(s8 *)(effect_base + 0x2D);

                if (value != 0) {
                    return value;
                }
                return 0x100;
            }
        }
    }
    {
        register s32 temp ASM_REG("$2");
        register s32 signed_orig ASM_REG("$3");

        temp = (u32)orig << 24;
        signed_orig = temp >> 24;
        if (signed_orig == 0xE) {
            return *(volatile u8 *)&a0->field_0x28 < 1;
        }
        temp = 0xD;
        if (signed_orig != temp) {
            temp = 0;
        } else {
            temp = 0;
            signed_orig = *((volatile s32 *)&a0->field_0x14);
        }
        return temp;
    }
}
