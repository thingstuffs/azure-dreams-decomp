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

s32 func_80016B5C(void)
{
    s32 result;
    s32 index;
    s32 value;
    s32 selector;
    s32 call_arg;
    u8 *entry;
    void **dispatch;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6, &&default_case
    };

    (void)keepalive;
    result = 2;
    func_800185C0(0x9AF);
    func_800185C0(0x9B0);
    func_800185C0(0x9B1);
    func_800185C0(0x9B2);
    func_800185C0(0x9B3);
    func_800185C0(0x9B4);
    func_800185C0(0x9B5);
    func_800185C0(0x9B6);

    index = 1;
    dispatch = D_8001601C;
loop:
        entry = D_80010000.root->entries;
        entry += index;
        value = entry[0x3608];
        selector = value - 5;
        if ((u32)selector >= 8) {
            goto default_case;
        }
        goto *dispatch[selector];

case_0:
        call_arg = 0x9AF;
        goto selected_call;
case_1:
        call_arg = 0x9B0;
        goto selected_call;
case_2:
        call_arg = 0x9B1;
        goto selected_call;
case_3:
        call_arg = 0x9B2;
        goto selected_call;
case_4:
        call_arg = 0x9B3;
        goto selected_call;
case_5:
        call_arg = 0x9B4;
        goto selected_call;
case_6:
        call_arg = 0x9B5;
        goto selected_call;

default_case:
        result -= 1;
        call_arg = 0x9B6;
        if (result != 0) {
            goto after_call;
        }

selected_call:
        func_80018548(call_arg);

after_call:
        index -= 1;
        if (index >= 0) {
            goto loop;
        }

    return result;
}
