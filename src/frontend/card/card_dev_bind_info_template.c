#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
void func_80047358(s32, void *, s32);            /* extern */

/* Processes the context using the four-entry table at D_80408D74. */
void card_dev_bind_info_template(s32 context) {
    func_80047358(context, &D_80408D74, 4);
}
