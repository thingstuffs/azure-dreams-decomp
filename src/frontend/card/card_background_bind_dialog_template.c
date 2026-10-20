#include "common.h"
#include "m2c_compat.h"

s32 func_80047358(s32, void *, s32);
extern M2C_UNK D_80408CE8;

/* Forwards the context with D_80408CE8 and the fixed value 7. */
void card_background_bind_dialog_template(s32 context) {
    func_80047358(context, &D_80408CE8, 7);
}
