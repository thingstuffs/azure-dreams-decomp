#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"

extern void func_80404618(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void card_devkit_refresh_save_slot_pair_highlights(void *ptr) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == *((s32 *)ptr + 0xB)) {
            func_80404618(((void **)ptr)[i + 1], 1);
        } else if (i == *((s32 *)ptr + 0xA)) {
            card_devkit_set_window_selection_marker(((void **)ptr)[i + 1], 1);
        } else {
            func_80404668(((void **)ptr)[i + 1]);
        }
    }
    func_80405A00(*((s32 *)ptr + 7), *((s32 *)ptr + 0xA));
}
