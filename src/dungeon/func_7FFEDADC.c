#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8008B0E8();


typedef struct S_8008B23C_0 {
    u32 unk_00;
    s32 unk_04;
} S_8008B23C_0;   /* var_s0 in func_8008B23C */

/* Process packed fields from each entry until the zero sentinel. */
void func_8008B23C(u8 *entries) {
    u8 *entry;
    u32 packed_fields;

    entry = entries;
    if (((S_8008B23C_0 *)entry)->unk_04 != 0) {
        do {
            packed_fields = ((S_8008B23C_0 *)entry)->unk_00;
            func_8008B0E8(
                (packed_fields >> 0x17) & 1,
                (u32)(packed_fields & 0x3F000000) >> 0x18,
                (u32)(packed_fields & 0x7F0000) >> 0x10
            );
            entry += 8;
        } while (((S_8008B23C_0 *)entry)->unk_04 != 0);
    }
}
