#include "common.h"
#include "m2c_compat.h"

extern void func_80024610(void *, void *, void *, s32, s32, M2C_UNK *, s32, s32);
extern s32 func_800644B8();
extern s32 func_80064584();

typedef struct S_818B1334_0 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} S_818B1334_0;   /* var_s2 in func_818B1334 */

typedef struct S_818B1334_1 {
    u8 pad_00[0x10];
    s16 unk_10;
} S_818B1334_1;   /* arg0 in func_818B1334 */

typedef struct S_818B1334_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818B1334_2;   /* var_s2_2 in func_818B1334 */

typedef struct S_818B1334_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818B1334_3;   /* arg1 in func_818B1334 */

/* Build a circular lookup table and submit eight phase-shifted entries. */
s32 func_818B1334(S_818B1334_1 *source, S_818B1334_3 *target, void *context) {
    M2C_UNK circle_values[34];
    M2C_UNK *circle_entry;
    register M2C_UNK *circle_table;
    s16 radius;
    s32 entry_angle;
    s32 circle_angle;
    s32 phase;
    s32 phase_bias;
    s32 index_bias;
    s32 circle_index;
    s32 entry_index;
    u16 angle_offset;
    void *offset_cursor;
    void *source_arg;

    circle_table = circle_values;
    circle_index = 0x10;
    circle_entry = circle_table + 16;
    do {
        index_bias = circle_index;
        if (circle_index < 0) {
            index_bias = circle_index + 0xF;
        }
        circle_angle = (circle_index - ((index_bias >> 4) * 0x10)) << 8;
        ((S_818B1334_0 *)circle_entry)->unk_00 = (s32) (func_800644B8(circle_angle) >> 4);
        ((S_818B1334_0 *)circle_entry)->unk_44 = (s32) (func_80064584(circle_angle) >> 4);
        circle_entry -= 1;
    } while (--circle_index >= 0);
    entry_index = 0;
    offset_cursor = source;
    do {
        phase = source->unk_10 - entry_index;
        phase_bias = phase;
        if (phase < 0) {
            phase_bias = phase + 0xF;
        }
        radius = (func_800644B8((phase - ((phase_bias >> 4) * 0x10)) << 9) >> 9) + 0x20;
        func_80064584(entry_index << 0xA);
        source_arg = source;
        ASM_KEEP(source_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_offset = ((S_818B1334_2 *)offset_cursor)->unk_1A;
        offset_cursor += 2;
        entry_angle = entry_index << 0x11;
        entry_index += 1;
        func_80024610(source_arg, target, context, radius, (s32) (s16) (target->unk_0A - angle_offset), circle_table, 0xFF, entry_angle >> 0x10);
    } while (entry_index < 8);
    return 0;
}
