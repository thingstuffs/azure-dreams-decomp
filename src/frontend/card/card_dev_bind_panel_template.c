#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
void func_80047358(s32, void *, s32);            /* extern */

/* Pass the caller's context and fixed data to func_80047358. */
void card_dev_bind_panel_template(s32 context) {
    func_80047358(context, &D_80408C9C, 0x12);
}
