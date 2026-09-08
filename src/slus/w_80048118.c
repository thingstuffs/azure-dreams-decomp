#include "common.h"

extern void func_800481E0(void);
extern void func_80047C00(void);
extern void *func_80047CD8(s16 a0);
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);
extern int func_800499DC(int *a0);

/* Gets the code's slot, refreshing for code 0x38, and initializes callback state on success. */
void *func_80048118(s32 packed_code, s32 *callback_state)
{
    s16 code = (s16)packed_code;
    void *slot;

    if (code == 0x38) {
        func_800481E0();
        func_80047C00();
    }
    slot = func_80047CD8(code);
    if (slot != 0) {
        *callback_state = 0;
        func_8003E4FC(0xFF, (void *)func_800499DC, callback_state);
    }
    return slot;
}
