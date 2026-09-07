#include "common.h"

extern s32 func_80024610();
extern s32 func_800644B8();
extern s32 func_80064584();

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

s32 func_818B11B4(void *arg0, void *arg1, s32 arg2) {
    s32 sp20[34];
    s32 *buffer;
    s32 *cursor;
    s16 angle;
    s32 shifted_index;
    s32 trig_arg;
    s32 position;
    s32 segment_count;
    s32 quotient_arg;
    s32 quotient;
    s32 table_index;
    s32 index;
    s32 count;
    u16 height;
    void *height_cursor;
    register void *call_arg0 ASM_REG("$4");

    buffer = sp20;
    table_index = 0x10;
    cursor = &sp20[16];
    do {
        quotient = table_index;
        if (table_index < 0) {
            quotient = table_index + 0xF;
        }
        trig_arg = (table_index - ((quotient >> 4) * 0x10)) << 8;
        cursor[0] = func_800644B8(trig_arg) >> 4;
        cursor[17] = func_80064584(trig_arg) >> 4;
        ASM_SCHED_BARRIER();
        table_index--;
        cursor--;
    } while (table_index >= 0);

    segment_count = (s32)(FIELD(arg0, u16, 0x16) << 0x10) >> 0x12;
    count = 8;
    if (segment_count < 9) {
        count = segment_count;
    }

    index = 0;
    if (count > 0) {
        height_cursor = arg0;
        do {
            position = FIELD(arg0, s16, 0x10) - index;
            quotient_arg = position;
            if (position < 0) {
                quotient_arg = position + 0xF;
            }
            angle = (func_800644B8((position - ((quotient_arg >> 4) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(index << 9);
            call_arg0 = arg0;
            ASM_KEEP(call_arg0);
            height = FIELD(height_cursor, u16, 0x1A);
            height_cursor = (u8 *)height_cursor + 2;
            shifted_index = index << 0x11;
            index++;
            func_80024610(call_arg0, arg1, arg2, angle,
                         (u32)(s16)(FIELD(arg1, u16, 0xA) - height),
                         buffer, 0xFF, shifted_index >> 0x10);
        } while (index < count);
    }
    return 0;
}
