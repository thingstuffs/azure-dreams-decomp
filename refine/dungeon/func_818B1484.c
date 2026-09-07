#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern M2C_UNK func_80024610();
extern s32 func_800644B8();
extern s32 func_80064584();

typedef struct S_818B1484_0 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} S_818B1484_0;   /* var_s2 in func_818B1484 */

typedef struct S_818B1484_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x4];
    u16 unk_16;
} S_818B1484_1;   /* arg0 in func_818B1484 */

typedef struct S_818B1484_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818B1484_2;   /* var_s2_2 in func_818B1484 */

typedef struct S_818B1484_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818B1484_3;   /* arg1 in func_818B1484 */

/* Builds a trigonometric lookup table and processes the remaining effect entries. */
s32 func_818B1484(S_818B1484_1 *effect, S_818B1484_3 *target, M2C_UNK context) {
    void *effect_arg;
    s32 wave_table[34];
    s32 *table_ptr;
    s32 *sample_ptr;
    s16 entry_scale;
    s32 entry_arg;
    s32 sample_angle;
    s32 phase;
    s32 phase_rounded;
    s32 index_rounded;
    s32 sample_index;
    s32 entry_index;
    u16 entry_offset;
    void *entry_ptr;

    table_ptr = wave_table;
    sample_index = 0x10;
    sample_ptr = &wave_table[16];
    do {
        index_rounded = sample_index;
        if (sample_index < 0) {
            index_rounded = sample_index + 0xF;
        }
        sample_angle = (sample_index - ((index_rounded >> 4) * 0x10)) << 8;
        ((S_818B1484_0 *)sample_ptr)->unk_00 = (u32) (func_800644B8(sample_angle) >> 4);
        ((S_818B1484_0 *)sample_ptr)->unk_44 = (s32) (func_80064584(sample_angle) >> 4);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        sample_index -= 1;
        sample_ptr--;
    } while (sample_index >= 0);
    entry_index = ((s32) (effect->unk_16 << 0x10) >> 0x12) + 1;
    if (entry_index < 8) {
        entry_ptr = (void *) ((entry_index << 1) + (u32) effect);
        do {
            phase = effect->unk_10 - entry_index;
            phase_rounded = phase;
            if (phase < 0) {
                phase_rounded = phase + 0xF;
            }
            entry_scale = (func_800644B8((phase - ((phase_rounded >> 4) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(entry_index << 9);
            effect_arg = effect;
            ASM_KEEP(effect_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
            entry_offset = ((S_818B1484_2 *)entry_ptr)->unk_1A;
            entry_ptr += 2;
            entry_arg = entry_index << 0x11;
            entry_index += 1;
            func_80024610(effect_arg, target, context, entry_scale,
                         (s32) (s16) (target->unk_0A - entry_offset),
                         table_ptr, 0xFF, entry_arg >> 0x10);
        } while (entry_index < 8);
    }
    return 0;
}
