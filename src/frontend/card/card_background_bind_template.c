#include "common.h"
#include "m2c_compat.h"

s32 func_80047358(s32, void *, s32);
extern M2C_UNK D_80408CB8;

/* Calls func_80047358 with the supplied context, D_80408CB8, and 10. */
void card_background_bind_template(s32 context) {
    func_80047358(context, &D_80408CB8, 0xa);
}
