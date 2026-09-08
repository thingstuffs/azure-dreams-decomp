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

/* Returns an effect value, 0x100 for a zero-valued match, or a type-specific fallback. */
s32 func_80042900(S_80042900 *entry, s32 effect_id)
{
    s32 effect_type = effect_id;
    register s32 saved_id ASM_REG("$7") = effect_id;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register u8 *effect_base ASM_REG("$3") = (u8 *)entry + 6;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 effect_index;

    effect_type = (u32)effect_type << 24;
    effect_type >>= 24;
    if (effect_type != 0) {
        for (effect_index = 3; effect_index >= 0; effect_index--, effect_base -= 2) {
            if (*(s8 *)(effect_base + 0x2C) == effect_type) {
                s32 effect_value = *(s8 *)(effect_base + 0x2D);

                if (effect_value != 0) {
                    return effect_value;
                }
                return 0x100;
            }
        }
    }
    {
        s32 result;
        s32 fallback_type;

        result = (u32)saved_id << 24;
        fallback_type = result >> 24;
        if (fallback_type == 0xE) {
            return *(volatile u8 *)&entry->field_0x28 < 1;
        }
        result = 0xD;
        if (fallback_type != result) {
            result = 0;
        } else {
            result = 0;
            fallback_type = *((volatile s32 *)&entry->field_0x14);
        }
        return result;
    }
}
