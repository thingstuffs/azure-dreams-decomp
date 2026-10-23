#include "common.h"

extern u8 D_800136B8;
extern void *town_map_entry_list[];
extern u8 town_map_event_kind;
extern u8 D_800D1A0C[];
extern u8 town_map_primary_entry[];
extern u8 town_map_secondary_entry[];
extern u8 town_map_tertiary_entry[];
extern u8 D_800D1D54[];
extern u8 D_800D1D5C[];
extern u8 D_800D1D64[];
extern u8 D_800D1D6C[];
extern u8 D_800D1DB4[];
extern u8 D_800D1DBC[];
extern u8 D_800D1DC4[];
extern u8 D_800D1DCC[];
extern u8 D_800D1DD4[];
extern u8 D_800D1DDC[];
extern u8 D_800D1DE4[];
extern u8 D_800D1DEC[];
extern u8 town_map_optional_entry[];
extern u8 town_map_variants[];
extern u8 town_map_selection_state[];

/* Builds a null-terminated entry list for the current map kind and variant. */
void build_map_variant_entry_list(void) {
    s32 count;
    s32 i;
    u32 records;
    u8 *state;
    u32 table;
    u8 *map_records;

    count = 1;
    town_map_entry_list[0] = town_map_primary_entry;
    if ((u32)(town_map_event_kind - 0x16) >= 2U) {
        count = 3;
        town_map_entry_list[1] = town_map_secondary_entry;
        town_map_entry_list[2] = town_map_tertiary_entry;
    }
    map_records = town_map_variants;
    switch (map_records[town_map_selection_state[6] << 5]) {
    case 5:
        switch ((*(u8 *)0x800136B8)) {
        default: town_map_entry_list[count++] = D_800D1D54; break;
        case 0xB: town_map_entry_list[count++] = D_800D1D5C; break;
        case 0xC: town_map_entry_list[count++] = D_800D1D64; break;
        case 0xD: town_map_entry_list[count++] = D_800D1D6C; break;
        }
        town_map_entry_list[count++] = town_map_optional_entry;
        break;
    case 0xF:
        switch ((*(u8 *)0x800136B8)) {
        default: town_map_entry_list[count++] = D_800D1DB4; break;
        case 0xB: town_map_entry_list[count++] = D_800D1DBC; break;
        case 0xC: town_map_entry_list[count++] = D_800D1DC4; break;
        case 0xD: town_map_entry_list[count++] = D_800D1DCC; break;
        }
        town_map_entry_list[count++] = town_map_optional_entry;
        break;
    case 0x10:
        switch ((*(u8 *)0x800136B8)) {
        default: town_map_entry_list[count++] = D_800D1DD4; break;
        case 0xB: town_map_entry_list[count++] = D_800D1DDC; break;
        case 0xC: town_map_entry_list[count++] = D_800D1DE4; break;
        case 0xD: town_map_entry_list[count++] = D_800D1DEC; break;
        }
        town_map_entry_list[count++] = town_map_optional_entry;
        break;
    default:
        i = 0;
        records = (u32)town_map_variants;
        state = town_map_selection_state;
        table = (u32)D_800D1A0C;
        do {
            town_map_entry_list[count++] = ((void **)((*(u8 *)((state[6] << 5) + records) << 3) + table))[i];
            i++;
        } while (i < 2);
        break;
    }
    town_map_entry_list[count] = 0;
}
