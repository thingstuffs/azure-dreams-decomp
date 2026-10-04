#include "common.h"

typedef struct {
    u8 pad0[3];
    u8 kind;
    u8 byte4;
    u8 byte5;
    u8 byte6;
    u8 pad7;
    s16 field8;
    u8 padA[22];
} Record;

extern s32 func_80033B2C(s32);
extern Record D_800D2644[];
extern u8 D_800D2EA4[];

/* CheckBuildBuildingLandNo collects eligible land slots for a building and returns their count. */
s32 CheckBuildBuildingLandNo(record_key, slots_out)
u8 record_key;
s8 *slots_out;
{
    s8 *slots_start;
    Record *record;
    u8 slot_count;
    s32 slot;
    s32 record_id;
    s32 slot_index;
    u32 first_id;
    u32 second_id;
    u8 single_id;
    u8 *slot_pair;
    u8 *entry;
    Record *match_record;
    Record *match_records;

    slot_count = 0;
    {
        Record *records = D_800D2644;
        record = records + (record_key & 0xFF);
    }
    slots_start = slots_out;
    if (func_80033B2C(record->field8) == 0) {
        return 0;
    }

    switch (record->kind) {
    case 4:
    case 8:
    {
        u8 *selected_entry;
        u8 *filter_entry;
        u8 *slot_table_base;
        u8 *slot_row;
        u32 selected_id;

        Record *records = D_800D2644;
        selected_id = record_key & 0xFF;
        selected_entry = (u8 *)&records[selected_id];
        if (selected_entry[6] == 0) {
            break;
        }
        slot_table_base = (u8 *)0x80010000;
        slot = 0;
        filter_entry = selected_entry;
        do {
            slot_row = (u8 *)((u8)slot * 2 + (u32)slot_table_base);
            if ((slot_row[0x33A4] == filter_entry[6]) && (slot_row[0x33A5] != selected_id)) {
                *slots_out++ = slot;
                slot_count++;
            }
            slot++;
        } while ((u8)slot < 0x21);
        *slots_out = 0;
        return (u8)slot_count;
    }
    case 16:
    {
        u8 *pair_page;
        u8 *owner_page;
        Record *records = D_800D2644;
        s32 record_id = record_key & 0xFF;
        single_id = records[record_id].byte6;
        if (single_id == 0)
            break;
        pair_page = (u8 *)0x80010000;
        if (pair_page[0x33E6] == single_id) {
            owner_page = pair_page;
            if (owner_page[0x33E7] != record_id) {
                *slots_out++ = 0xB;
                slot_count++;
            }
        }
        break;
    }
    case 1:
    {
        u8 *entries;
        u8 *slots_page;
        s32 excluded_id = 0;
        slot = 0;
        slots_page = (u8 *)0x80010000;
        entries = &D_800D2EA4[0];
        record_id = record_key & 0xFF;
        match_records = D_800D2644;
        match_record = match_records + record_id;
        do {
            slot_index = slot & 0xFF;
            slot_pair = (u8 *)(slot_index * 2 + (u32)slots_page);
            first_id = slot_pair[0x33A4];
            if (first_id == record_id || (second_id = slot_pair[0x33A5], second_id == record_id)) {
                slots_out = slots_start;
                slot_count = 0;
                break;
            }
            entry = (u8 *)(slot_index * 8 + (u32)entries);
            if (entry[2] == match_record->byte4 &&
                entry[3] == match_record->byte5 &&
                first_id >= 0x2D) {
                excluded_id = 0x30;
                if (first_id != excluded_id && second_id == 0) {
                    *slots_out++ = slot;
                    slot_count++;
                }
            }
            slot++;
        } while ((u8)slot < 0x21);
        break;
    }
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    default:
        break;
    }
    *slots_out = 0;
    return (u8)slot_count;
}
