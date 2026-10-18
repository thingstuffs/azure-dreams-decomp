#include "common.h"

extern void memory_process_handles_and_mark_object(void *ptr);
extern void func_80406678(void *ptr);
extern void allocate_initializes(void *ptr, s32 value);

void card_boot_clear_menu_state(void *ptr) {
    s32 value;

    memory_process_handles_and_mark_object((u8 *)ptr - 0x20);
    value = *(s32 *)ptr;
    if (value == 0) {
        func_80406678(*(void **)((u8 *)ptr + 0x14));
        return;
    } else {
        allocate_initializes(*(void **)((u8 *)ptr + 0x14), value);
    }
}
