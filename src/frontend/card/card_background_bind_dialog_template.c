#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"


/* Forwards the context with D_80408CE8 and the fixed value 7. */
s32 card_background_bind_dialog_template(struct CardDevMenuEntry **entries) {
    return func_80047358(entries, &D_80408CE8, 7);
}
