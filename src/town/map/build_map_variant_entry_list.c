#include "common.h"
#include "town/map.h"
#include "town/data.h"
#include "town/map/variant_data.h"
#include "town/map/map_cursor_input_g00641.h"
#include "town/map/event_entry_data.h"

extern void *D_800D1A0C[][2];
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
/* Builds a null-terminated entry list for the current map kind and variant. */
void build_map_variant_entry_list(void) {
    s32 count;
    s32 i;
    /* BYTES: reload the variant table address on the default switch path. */
    unsigned long records;
    u8 *state;
    TownMapVariantRecord *map_records;

    count = 1;
    town_map_entry_list[0] = town_map_primary_entry;
    if ((u32)(town_map_event_kind - 0x16) >= 2U) {
        count = 3;
        town_map_entry_list[1] = town_map_secondary_entry;
        town_map_entry_list[2] = town_map_tertiary_entry;
    }
    map_records = town_map_variants;
    switch (map_records[town_map_selection_state[6]].entry_kind) {
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
        records = (unsigned long)town_map_variants;
        state = town_map_selection_state;
        do {
            TownMapVariantRecord *record = (TownMapVariantRecord *)(state[6] * sizeof(*record) + records);

            town_map_entry_list[count++] = D_800D1A0C[record->entry_kind][i];
            i++;
        } while (i < 2);
        break;
    }
    town_map_entry_list[count] = 0;
}
