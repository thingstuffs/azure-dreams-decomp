#include "common.h"

extern s32 func_8004A658(s32 a0, s32 a1);

/* Fills ten output slots from the current page of records, zeroing unused slots. */
void func_800B2FF8(s32 **outputs, s32 *page_info, s32 record_table) {
    s32 slot;
    s32 page;
    s32 record_index;
    u8 **record_ptr;
    s32 **output_ptr;
    u8 *record;
    s32 **empty_slot;
    s32 *output;

    slot = 0;
    page = page_info[0];
    output_ptr = outputs;
    record_index = page * 10;
    record_ptr = (u8 **)((record_index * 4) + record_table);

    for (; slot < 10 && record_index < page_info[3]; record_index++) {
        slot++;
        record = *record_ptr;
        record_ptr++;
        *(*output_ptr) = func_8004A658(record[1], record[0]);
        output_ptr++;
    }
    if (slot < 10) {
        for (empty_slot = (s32 **)((s32)(slot * 4) + (s32)outputs); slot < 10; empty_slot++) {
            slot++;
            output = *empty_slot;
            do {
            } while (0);
            *output = 0;
        }
    }
}
