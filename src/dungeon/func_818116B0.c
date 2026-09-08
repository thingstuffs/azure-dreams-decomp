#include "common.h"

extern void *D_80026690;
void func_8002640C(void);

/* Apply the current step to the object and reset the sequence after five steps. */
void func_800266B0(s32 *step) {
    s32 step_value = *step << 10;

    *(s16 *) (*(s32 *) ((u8 *) step + 0x64) + 6) = step_value;
    *step += 1;
    if (*step >= 5) {
        *step = 0;
        *(void **) ((u8 *) step - 0x10) = &D_80026690;
    }
    func_8002640C();
}
