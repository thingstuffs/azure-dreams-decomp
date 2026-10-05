#include "common.h"

extern u16 func_80095978(void *position, void *out_value);
extern void func_80095A94(void *obj, s16 base_value, void *vec_ptr);
extern void func_80098928(void *record, void *setup_value, s32 init_value);

extern u8 D_800CFCB4[];
extern u8 D_800FE488[];

/* Conditionally refreshes object data before passing it to func_80098928. */
void func_800982EC(void *context, void *object, s32 mode) {
    void *state;

    if (D_800CFCB4[0x3B] != 0) {
        state = *(void **)(*(void **)(D_800CFCB4 + 0x20) + 8);
        if ((*(s32 *)((u8 *)state + 0xC) != 0) ||
            (*(s32 *)((u8 *)state + 0x10) != 0) ||
            (*(s32 *)((u8 *)state + 0x14) != 0)) {
            func_80095A94(object, func_80095978(object, D_800FE488),
                          D_800FE488);
        }
    } else {
        func_80095A94(object, func_80095978(object, D_800FE488),
                      D_800FE488);
    }
    func_80098928(context, object, mode);
}
