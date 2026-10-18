#include "common.h"

extern void card_devkit_set_window_selection_marker(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void card_devkit_highlight_selected_load_slot(void *ptr) {
    s32 i;

    i = 0;
    while (1) {
        if (i == *(s32 *)((u8 *)ptr + 0x2C)) {
            card_devkit_set_window_selection_marker(*(void **)((u8 *)ptr + i * 4 + 0xC), 1);
        } else {
            func_80404668(*(void **)((u8 *)ptr + i * 4 + 0xC));
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    func_80405A00(*(s32 *)((u8 *)ptr + 4), *(s32 *)((u8 *)ptr + 0x2C));
}
