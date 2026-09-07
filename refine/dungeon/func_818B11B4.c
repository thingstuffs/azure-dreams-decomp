#include "common.h"

typedef struct S_818B11B4_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x4];
    u16 unk_16;
} S_818B11B4_0;   /* arg0 in func_818B11B4 */

typedef struct S_818B11B4_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818B11B4_1;   /* height_cursor in func_818B11B4 */

typedef struct S_818B11B4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818B11B4_2;   /* arg1 in func_818B11B4 */


extern s32 func_80024610();
extern s32 func_800644B8();
extern s32 func_80064584();


/* Builds a trigonometric table and processes up to eight height-offset segments. */
s32 func_818B11B4(S_818B11B4_0 *source, S_818B11B4_2 *height_ref, s32 segment_param) {
    s32 trig_table[34];
    s32 *trig_buffer;
    s32 *trig_cursor;
    s16 angle;
    s32 scaled_segment;
    s32 table_angle;
    s32 phase;
    s32 segment_count;
    s32 biased_phase;
    s32 biased_index;
    s32 table_index;
    s32 segment_index;
    s32 segment_limit;
    u16 height;
    void *height_cursor;
    void *segment_source;

    trig_buffer = trig_table;
    table_index = 0x10;
    trig_cursor = &trig_table[16];
    do {
        biased_index = table_index;
        if (table_index < 0) {
            biased_index = table_index + 0xF;
        }
        table_angle = (table_index - ((biased_index >> 4) * 0x10)) << 8;
        trig_cursor[0] = func_800644B8(table_angle) >> 4;
        trig_cursor[17] = func_80064584(table_angle) >> 4;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        table_index--;
        trig_cursor--;
    } while (table_index >= 0);

    segment_count = (s32)(source->unk_16 << 0x10) >> 0x12;
    segment_limit = 8;
    if (segment_count < 9) {
        segment_limit = segment_count;
    }

    segment_index = 0;
    if (segment_limit > 0) {
        height_cursor = source;
        do {
            phase = source->unk_10 - segment_index;
            biased_phase = phase;
            if (phase < 0) {
                biased_phase = phase + 0xF;
            }
            angle = (func_800644B8((phase - ((biased_phase >> 4) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(segment_index << 9);
            segment_source = source;
            ASM_KEEP(segment_source);   /* MATCH pin: retail schedule: same instructions, different order without it */
            height = ((S_818B11B4_1 *)height_cursor)->unk_1A;
            height_cursor = (u8 *)height_cursor + 2;
            scaled_segment = segment_index << 0x11;
            segment_index++;
            func_80024610(segment_source, height_ref, segment_param, angle,
                         (u32)(s16)(height_ref->unk_0A - height),
                         trig_buffer, 0xFF, scaled_segment >> 0x10);
        } while (segment_index < segment_limit);
    }
    return 0;
}
