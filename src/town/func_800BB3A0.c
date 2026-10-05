#include "common.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 value[5];
} TownFiveWords;
extern TownFiveWords D_800894D0;

typedef struct S_800B8B00_0 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
    u8 unk_33A5;
} S_800B8B00_0;   /* temp_v1 in func_800B8B00 */

typedef struct S_800B8B00_1 {
    u8 pad_00[0x33A5];
    u8 unk_33A5;
} S_800B8B00_1;   /* temp_v1_2 in func_800B8B00 */

/* Stores a normalized code in its designated slot, avoiding duplicate code 9 entries. */
void func_800B8B00(s32 code) {
    s8 stored_code;
    TownFiveWords slot_ids;
    s16 code_index;
    s32 scan_count;
    s32 duplicate_code;
    S_800B8B00_0 *scan_slot;
    S_800B8B00_1 *free_slot;
    u8 *scan_base;
    u8 *free_base;
    u8 *store_base;

    stored_code = code;
    slot_ids = D_800894D0;
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
            scan_slot = (u8 *)((u32)(slot_ids.value[scan_count] * 2) + (u32)scan_base);
            if (scan_slot->unk_33A4 == duplicate_code) return;
            if (scan_slot->unk_33A5 == duplicate_code) return;
            scan_count += 1;
        } while (scan_count < 5);
        scan_count = 0;
        free_base = (u8 *)0x80010000;
        do {
            free_slot = (u8 *)((u32)(slot_ids.value[scan_count] * 2) + (u32)free_base);
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
        store_base = (u8 *)0x80010000;
        store_base[0x33A7] = stored_code;
        return;
    case 0x10:
    case 0x11:
        store_base = (u8 *)0x80010000;
        store_base[0x33A9] = stored_code;
        return;
    case 0x37:
        stored_code = 3;
                /* fallthrough */
store_group_code:
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3F:
    case 0x40:
    case 0x41:
        store_base = (u8 *)0x80010000;
        store_base[0x33BB] = stored_code;
        return;
    case 0x38:
        stored_code = 2;
        goto store_group_code;
    case 0x3E:
        stored_code = 1;
        goto store_group_code;
    case 0x3:
    case 0x4:
        store_base = (u8 *)0x80010000;
        store_base[0x33C5] = stored_code;
        return;
    case 0xE:
    case 0xF:
        store_base = (u8 *)0x80010000;
        store_base[0x33C7] = stored_code;
        return;
    case 0x6:
    case 0x2C:
        store_base = (u8 *)0x80010000;
        store_base[0x33C9] = stored_code;
        return;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        store_base = (u8 *)0x80010000;
        store_base[0x33E7] = stored_code;
        break;
    }
}
