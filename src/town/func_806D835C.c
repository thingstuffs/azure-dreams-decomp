#include "common.h"

typedef struct Func806D835CRoot {
    u8 pad0[0x38];
    u8 *entries;
} Func806D835CRoot;

extern Func806D835CRoot *D_80016000;
extern void func_800185C0(s32);
extern void func_80018548(s32);

/* Selects IDs 0x9AF-0x9B6 from two entry codes and returns the match count. */
s32 func_80016B5C(void)
{
    s32 match_count;
    s32 entry_index;
    s32 entry_code;
    s32 selected_id;
    u8 *entry_data;
    match_count = 2;
    func_800185C0(0x9AF);
    func_800185C0(0x9B0);
    func_800185C0(0x9B1);
    func_800185C0(0x9B2);
    func_800185C0(0x9B3);
    func_800185C0(0x9B4);
    func_800185C0(0x9B5);
    func_800185C0(0x9B6);

    entry_index = 1;
    do {
        entry_data = D_80016000->entries;
        entry_data += entry_index;
        entry_code = entry_data[0x3608];
        switch (entry_code) {
        case 5:
            selected_id = 0x9AF;
            break;
        case 6:
            selected_id = 0x9B0;
            break;
        case 8:
            selected_id = 0x9B1;
            break;
        case 9:
            selected_id = 0x9B2;
            break;
        case 10:
            selected_id = 0x9B3;
            break;
        case 11:
            selected_id = 0x9B4;
            break;
        case 12:
            selected_id = 0x9B5;
            break;
        default:
            match_count -= 1;
            selected_id = 0x9B6;
            if (match_count != 0) {
                continue;
            }
            break;
        }
        func_80018548(selected_id);
    } while (--entry_index >= 0);

    return match_count;
}
