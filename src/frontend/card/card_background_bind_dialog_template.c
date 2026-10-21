#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

s32 func_80047358(s32, void *, s32);

/* Forwards the context with D_80408CE8 and the fixed value 7. */
void card_background_bind_dialog_template(s32 context) {
    func_80047358(context, &D_80408CE8, 7);
}
