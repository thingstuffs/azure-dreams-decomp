#include "common.h"

typedef struct Func806D835CRoot {
    u8 pad0[0x38];
    u8 *entries;
} Func806D835CRoot;

typedef struct Func806D835CPage {
    u8 pad0[0x6000];
    Func806D835CRoot *root;
} Func806D835CPage;

extern Func806D835CPage D_80010000;
extern void *D_8001601C[];
extern void func_800185C0(s32);
extern void func_80018548(s32);

/* Selects IDs 0x9AF-0x9B6 from two entry codes and returns the match count. */
s32 func_80016B5C(void)
{
    s32 match_count;
    s32 entry_index;
    s32 entry_code;
    s32 case_index;
    s32 selected_id;
    u8 *entry_data;
    void **dispatch_table;
    static void *const case_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6, &&default_case
    };

    (void)case_labels;
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
    dispatch_table = D_8001601C;
loop:
        entry_data = D_80010000.root->entries;
        entry_data += entry_index;
        entry_code = entry_data[0x3608];
        case_index = entry_code - 5;
        if ((u32)case_index >= 8) {
            goto default_case;
        }
        goto *dispatch_table[case_index];

case_0:
        selected_id = 0x9AF;
        goto selected_call;
case_1:
        selected_id = 0x9B0;
        goto selected_call;
case_2:
        selected_id = 0x9B1;
        goto selected_call;
case_3:
        selected_id = 0x9B2;
        goto selected_call;
case_4:
        selected_id = 0x9B3;
        goto selected_call;
case_5:
        selected_id = 0x9B4;
        goto selected_call;
case_6:
        selected_id = 0x9B5;
        goto selected_call;

default_case:
        match_count -= 1;
        selected_id = 0x9B6;
        if (match_count != 0) {
            goto after_call;
        }

selected_call:
        func_80018548(selected_id);

after_call:
        entry_index -= 1;
        if (entry_index >= 0) {
            goto loop;
        }

    return match_count;
}
