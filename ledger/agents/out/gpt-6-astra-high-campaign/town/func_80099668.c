#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80096B50(s32);                            /* extern */
M2C_UNK func_80096C3C();                            /* extern */
extern s16 D_8006ADD4;

/* Dispatch to the parameterized handler in state 12 or the default handler otherwise. */
void func_80096DC8(s32 handler_param) {
    if (D_8006ADD4 == 0xC) {
        func_80096B50(handler_param);
        return;
    }
    func_80096C3C();
}
