#include "common.h"

typedef struct {
    s32 words[0x15];
} Record84;

extern s32 find_first_vacant_record(void *, s32);
extern u8 *find_unused_default_pool_slot(void);
extern Record84 town_slot_snapshot;

/* Copies a record into the pointer table and initializes extra data for tag 0x13. */
void copy_a_pointer_table_initializes_extra_data_tag_hex_13(s32 entry_index, void *source) {
    u8 *record;
    s32 tag;
    s32 data_slot;
    u8 *table_base;

    record = find_unused_default_pool_slot();
    record[0] = ((u8 *)source)[0];
    record[1] = ((u8 *)source)[1];
    record[2] = ((u8 *)source)[2];
    tag = record[1];
    record[3] = ((u8 *)source)[3];
    if (tag == 0x13) {
        data_slot = find_first_vacant_record((void *)0x800102F0, 0x14);
        *(Record84 *)(0x800102F0 + data_slot * 0x54) = town_slot_snapshot;
        record[3] = (record[3] & 0xC0) | data_slot;
    }
    table_base = (u8 *)0x80010000;
    *(void **)(table_base + entry_index * 4 + 0x29C) = record;
    *(s32 *)(table_base + entry_index * 4 + 0x2A0) = 0;
}
