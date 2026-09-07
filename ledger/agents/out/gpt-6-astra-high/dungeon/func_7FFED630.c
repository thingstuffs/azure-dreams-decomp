#include "common.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 h2;
    s32 w4;
} Record;

extern Record D_800CF720[];
extern u8 D_801131B8[];
extern s32 func_8008ACE8(s32, void *);
extern void func_8008ACAC(s32, s32, s32);

/* Shifts records up one slot and processes their data with the given offset. */
void func_8008AD90(s32 record_count, s32 data_offset) {
    s32 data_addr;
    s32 record_value;
    s32 src_index;
    s32 dst_index;
    Record *dst_record;
    Record *src_record;
    s32 records_base;
    u8 *state;

    dst_index = record_count;
    if (dst_index != 0) {
        records_base = (s32)D_800CF720;
        state = D_801131B8;
        do {
            dst_record = (Record *)(dst_index * 8 + records_base);
            src_index = dst_index - 1;
            src_record = (Record *)(src_index * 8 + records_base);
            dst_record->b0 = src_record->b0;
            dst_record->b1 = src_record->b1;
            dst_record->h2 = src_record->h2;
            record_value = src_record->w4;
            dst_record->w4 = record_value;
            data_addr = *(s32 *)(state + 0x2c) + func_8008ACE8(src_index, dst_record);
            func_8008ACAC(data_addr + data_offset, data_addr, record_value);
            dst_index = src_index;
        } while (dst_index != 0);
    }
}
