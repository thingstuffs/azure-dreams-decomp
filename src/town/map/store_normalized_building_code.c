#include "common.h"
#include "town/map.h"
#include "shared/game_state.h"


typedef struct {
    s32 value[5];
} TownFiveWords;
extern TownFiveWords building_pair_indices;

typedef struct S_800B8B00_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B8B00_0;

typedef struct S_800B8B00_1 {
    u8 pad_00[0x33A5];
    u8 unk_33A5;
} S_800B8B00_1;

/* Stores a normalized code in its designated slot, avoiding duplicate code 9 entries. */
void store_normalized_building_code(s32 code) {
    s8 stored_code;
    TownFiveWords slot_ids;
    s16 code_index;
    s32 scan_count;
    s32 duplicate_code;
    S_800B8B00_0 *scan_slot;
    S_800B8B00_1 *free_slot;
    u8 *scan_base;
    u8 *free_base;

    stored_code = code;
    slot_ids = building_pair_indices;
    code_index = code - 1;
    switch (code_index) {
    case 0x5:
    case 0x7:
    case 0x8:
    case 0xA:
    case 0xB:
    case 0x29:
    case 0x2A:
        stored_code = 9;
        scan_count = 0;
        scan_base = (u8 *)0x80010000;
        duplicate_code = 9;
        do {
            scan_slot = (u8 *)((u32)(slot_ids.value[scan_count] * 2) + (unsigned long)scan_base);
            if (scan_slot->unk_33A4 == duplicate_code) return;
            if (scan_slot->unk_33A5 == duplicate_code) return;
            scan_count += 1;
        } while (scan_count < 5);
        scan_count = 0;
        free_base = (u8 *)0x80010000;
        do {
            free_slot = (u8 *)((u32)(slot_ids.value[scan_count] * 2) + (unsigned long)free_base);
            if (free_slot->unk_33A5 == 0) {
                free_slot->unk_33A5 = stored_code;
                return;
            }
            scan_count += 1;
        } while (scan_count < 5);
        return;
    default:
        return;
    case 0x36:
        stored_code = 0xA;
                /* fallthrough */
    case 0x9:
    case 0x2B:
        GAME_STATE->building_slots[1][1] = stored_code;
        return;
    case 0x10:
    case 0x11:
        GAME_STATE->building_slots[2][1] = stored_code;
        return;
    case 0x37:
        stored_code = 3;
        GAME_STATE->building_slots[11][1] = stored_code;
        return;
    case 0x0:

    case 0x1:
    case 0x2:
    case 0x3F:
    case 0x40:
    case 0x41:
        GAME_STATE->building_slots[11][1] = stored_code;
        return;
    case 0x38:
        stored_code = 2;
        GAME_STATE->building_slots[11][1] = stored_code;
        return;
    case 0x3E:
        stored_code = 1;
        GAME_STATE->building_slots[11][1] = stored_code;
        return;
    case 0x3:
    case 0x4:
        GAME_STATE->building_slots[16][1] = stored_code;
        return;
    case 0xE:
    case 0xF:
        GAME_STATE->building_slots[17][1] = stored_code;
        return;
    case 0x6:
    case 0x2C:
        GAME_STATE->building_slots[18][1] = stored_code;
        return;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        GAME_STATE->building_slots[33][1] = stored_code;
        break;
    }
}
