#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"


/* Calls func_80047358 with the supplied context, D_80408CB8, and 10. */
s32 card_background_bind_template(s32 context) {
    return func_80047358(context, &D_80408CB8, 0xa);
}
