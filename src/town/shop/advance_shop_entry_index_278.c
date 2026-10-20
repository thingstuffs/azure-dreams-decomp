/* Relinked copy of town/func_808781C8 (func_808781C8.c); its step flag is 0x278 (twin 0x1F9), otherwise retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_00000F12[];
extern TownPair D_00000F28[];

extern s32 is_next_entry_zero_after_skipping(s32 index);
extern void func_80000858(s32 index, s32 value);
extern s32 dispatch_first_rejected_entry_b(void);
extern void func_80000BC8(u16 value);
extern void func_80000C18(s32 value);
extern s32 func_80000C6C(u16 value);

/* Advance the shop entry at `index`: start its 0x278 step when eligible, otherwise just clear it. */
s32 advance_shop_entry_index_278(s32 index) {
    if (func_80000C6C(D_00000F12[0]) == 0 &&
        func_80000C6C(0x278) != 0) {
        if (is_next_entry_zero_after_skipping(index) != 0) {
            func_80000BC8(D_00000F28[index].field_0);
            func_80000C18(0x278);
            return dispatch_first_rejected_entry_b();
        }
        func_80000858(index, 0);
        return index;
    }
    func_80000858(index, 0);
    return index;
}
