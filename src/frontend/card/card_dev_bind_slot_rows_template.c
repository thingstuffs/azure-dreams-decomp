#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

s32 func_80047358(s32, void *, s32);

/* Forward the context to func_80047358 with D_80408D64 and a fixed argument of 4. */
void card_dev_bind_slot_rows_template(s32 context) {
    func_80047358(context, &D_80408D64, 4);
}
