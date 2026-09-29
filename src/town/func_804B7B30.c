#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_80017B3C(void *, s32);
extern s32 func_80017F8C(void *, s32, s32);
extern s32 D_80018AF8;
extern s32 D_80019A30;

/* Updates shared state and increments the current table entry if the selector-10 check returns zero. */
s32 *func_804B7B30(s32 value, s32 unused, s32 selector) {
    Rec_D_80016000 *context;
    u8 *entry;
    s32 *count_ptr;
    u8 **table_ptr;
    u32 entry_offset;

    func_80017B3C(&D_80018AF8, value);
    if (selector == 10 && func_80017F8C(&D_80018AF8, value, 10) == 0) {
        context = D_80016000;
        count_ptr = (s32 *)((u8 *)context + 8);
        table_ptr = (u8 **)((u8 *)context + 0x40);
        entry_offset = *count_ptr * 8;
        entry = (u8 *)(entry_offset + (u32)*table_ptr);

        *entry += 1;
    }
    return &D_80019A30;
}
