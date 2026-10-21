#include "common.h"
#include "frontend/card/load.h"

extern s32 get_table_entry_by_flag(void);
extern s32 count_nonzero(void);
extern void func_80406C74(void *ptr);
extern void func_80406CB8(void *ptr);
extern void func_80406C2C(void);
extern void func_80406B9C(void);
extern u8 card_slot_header_cache[];

void reset_menu_object_state(void *ptr) {
    s32 idx;

    idx = *(s32 *)((u8 *)ptr + 0x2C);
    if (*(s32 *)(card_slot_header_cache + (idx << 7)) != 0) {
        *(void (**)(void))((u8 *)ptr - 0x10) = func_80406C2C;
        return;
    }
    if (get_table_entry_by_flag() >= 3) {
        *(void (**)(void))((u8 *)ptr - 0x10) = func_80406B9C;
        return;
    }
    if (count_nonzero() != 0) {
        func_80406C74(ptr);
        return;
    }
    func_80406CB8(ptr);
}
