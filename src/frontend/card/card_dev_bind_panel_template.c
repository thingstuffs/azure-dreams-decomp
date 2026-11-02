#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"

/* Pass the caller's context and fixed data to func_80047358. */
s32 card_dev_bind_panel_template(s32 context) {
    return func_80047358(context, &D_80408C9C, 0x12);
}
