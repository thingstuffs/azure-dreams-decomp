#include "common.h"
#include "frontend/card/save.h"
#include "frontend/card.h"

extern s32 process_slot_record_on_lookup_success(s32 slot_index);
extern void initialize_card_message_object_with_code_0xb(void *ptr);
extern void func_80406590(void);
extern void func_80405A3C(void);

/* Builds one of five save-slot windows per call, switching callbacks on a failed lookup or completion. */
void card_devkit_build_save_slot_windows(void *ptr) {
    void *base;
    s32 idx;

    base = ptr;
    idx = *(s32 *)((u8 *)base + 0x24);
    if (idx < 5) {
        if (process_slot_record_on_lookup_success(idx) != 0) {
            *(u8 **)((u8 *)base + 4 + idx * 4) = init_card_window_slot_object((u8 *)base - 0x20, idx);
            *(s32 *)((u8 *)base + 0x24) = *(s32 *)((u8 *)base + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)base + 0x34) = func_80406590;
            initialize_card_message_object_with_code_0xb((u8 *)base - 0x20);
            *(void (**)(void))((u8 *)base - 0x10) = func_80405A3C;
        }
    }
    if (idx == 5) {
        *(void (**)(void))((u8 *)base - 0x10) = func_80406590;
    }
}
