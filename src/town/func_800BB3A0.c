#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern volatile s8 D_800133A7;
extern volatile s8 D_800133A9;
extern volatile s8 D_800133BB;
extern volatile s8 D_800133C5;
extern volatile s8 D_800133C7;
extern volatile s8 D_800133C9;
extern volatile s8 D_800133E7;
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
    s32 *scan_id;
    s32 *free_id;
    register s32 scan_count ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 free_count ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 duplicate_code;
    S_800B8B00_0 *scan_slot;
    S_800B8B00_1 *free_slot;
    u8 *scan_base;
    u8 *free_base;
    register volatile u8 *store_base ASM_REG("$1");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

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
        scan_id = slot_ids.value;
check_duplicate:
        scan_slot = (u8 *)((u32)(*scan_id * 2) + (u32)scan_base);
        if (scan_slot->unk_33A4 != duplicate_code) {
            scan_count += 1;
            if (scan_slot->unk_33A5 != duplicate_code) {
                scan_id += 1;
                if (scan_count >= 5) {
                    free_count = 0;
                    free_base = (u8 *)0x80010000;
                    free_id = slot_ids.value;
find_empty_slot:
                    do {
                        free_slot = (u8 *)((u32)(*free_id * 2) + (u32)free_base);
                        free_count += 1;
                        if (free_slot->unk_33A5 == 0) {
                            free_slot->unk_33A5 = stored_code;
                            return;
                        }
                        free_id += 1;
                    } while (free_count < 5);
                    return;
                }
                goto check_duplicate;
            }
        }
    default:
        return;
    case 0x36:
        stored_code = 0xA;
        /* fallthrough */
    case 0x9:
    case 0x2B:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33A7] = stored_code;
        return;
    case 0x10:
    case 0x11:
        store_base = (volatile u8 *)0x80010000;
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
        store_base = (volatile u8 *)0x80010000;
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
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C5] = stored_code;
        return;
    case 0xE:
    case 0xF:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C7] = stored_code;
        return;
    case 0x6:
    case 0x2C:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33C9] = stored_code;
        return;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        store_base = (volatile u8 *)0x80010000;
        store_base[0x33E7] = stored_code;
        break;
    }
}
