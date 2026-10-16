#include "modules/dungeon_ovl_d54c.h"

void townShiftResourceEntriesAndData(s32 record_count, s32 data_offset) {
    s32 data_addr;
    s32 record_value;
    s32 src_index;
    s32 dst_index;
    ovl_d54c_7FFED630_Record *dst_record;
    ovl_d54c_7FFED630_Record *src_record;
    s32 records_base;
    u8 *state;

    dst_index = record_count;
    if (dst_index != 0) {
        records_base = (s32)D_800CF720;
        state = (u8 *)&D_801131B8;
        do {
            dst_record = (ovl_d54c_7FFED630_Record *)(dst_index * 8 + records_base);
            src_index = dst_index - 1;
            src_record = (ovl_d54c_7FFED630_Record *)(src_index * 8 + records_base);
            dst_record->b0 = src_record->b0;
            dst_record->b1 = src_record->b1;
            dst_record->h2 = src_record->h2;
            record_value = src_record->w4;
            dst_record->w4 = record_value;
            data_addr = *(s32 *)(state + 0x2c) + townSumResourceBytes(src_index);
            townCopyWordsBackwardFromOffset(data_addr + data_offset, data_addr, record_value);
            dst_index = src_index;
        } while (dst_index != 0);
    }
}
