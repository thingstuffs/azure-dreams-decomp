#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"


/* Forward the context to func_80047358 with D_80408D64 and a fixed argument of 4. */
s32 card_dev_bind_slot_rows_template(s32 context) {
    return func_80047358(context, &D_80408D64, 4);
}
