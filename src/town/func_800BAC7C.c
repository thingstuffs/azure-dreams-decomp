#include "common.h"

typedef struct S_800B83DC_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B83DC_0;   /* pair_a in CheckBuildBuildingLand */

typedef struct S_800B83DC_1 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B83DC_1;   /* pair_c in CheckBuildBuildingLand */



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

/* Implements CheckBuildBuildingLand by checking pair assignments and matching land attributes. */
s32 CheckBuildBuildingLand(s32 record_key) {
    s32 key;
    Record *record;
    s32 has_match;
    u32 first_id;
    u32 second_id;
    s32 slot;
    s32 record_id;
    u8 pair_id;
    s32 slot_index;
    u8 *pair;
    u8 *slot_pair;
    u8 *entry;
    Record *match_record;
    Record *match_records;
    u8 *pairs_page;
    u8 single_id;

    key = record_key;
    {
        Record *records = D_800D2644;
        record = records + (key & 0xFF);
    }
    has_match = 0;
    if (func_80033B2C(record->field8) == 0) return 0;
    switch (record->kind) {
    case 4:
    case 8: {
        Record *records = D_800D2644;
        s32 record_id = key & 0xFF;
        pair_id = records[record_id].byte6;
        if (pair_id == 0) return 0;
        slot = 0;
        pairs_page = (u8 *)0x80010000;
        do {
            pair = (u8 *)((u8)slot * 2 + (u32)pairs_page);
            if (((S_800B83DC_0 *)pair)->unk_33A4 == pair_id &&
                ((S_800B83DC_0 *)pair)->unk_33A5 != record_id) return 1;
            slot++;
        } while ((u8)slot < 0x21);
        return 0;
    }
    case 16: {
        u8 *pair_page;
        u8 *owner_page;
        Record *records = D_800D2644;
        s32 record_id = key & 0xFF;
        single_id = records[record_id].byte6;
        if (single_id == 0) return 0;
        pair_page = (u8 *)0x80010000;
        if (pair_page[0x33E6] == single_id) {
            owner_page = pair_page;
            if (owner_page[0x33E7] != record_id) return 1;
        }
        return 0;
    }
    case 1: {
        u8 *entries;
        u8 *slots_page;
        s32 excluded_id = 0;
        slot = 0;
        slots_page = (u8 *)0x80010000;
        entries = &D_800D2EA4[0];
        record_id = key & 0xFF;
        match_records = D_800D2644;
        match_record = match_records + record_id;
        do {
            slot_index = slot & 0xFF;
            slot_pair = (u8 *)(slot_index * 2 + (u32)slots_page);
            first_id = ((S_800B83DC_1 *)slot_pair)->unk_33A4;
            if (first_id == record_id) return 0;
            second_id = ((S_800B83DC_1 *)slot_pair)->unk_33A5;
            if (second_id == record_id) return 0;
            entry = (u8 *)(slot_index * 8 + (u32)entries);
            if (entry[2] == match_record->byte4 &&
                entry[3] == match_record->byte5 &&
                first_id >= 0x2D) {
                excluded_id = 0x30;
                if (first_id != excluded_id && second_id == 0) has_match = 1;
            }
            slot++;
        } while ((u8)slot < 0x21);
        return has_match;
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
    return 0;
}
