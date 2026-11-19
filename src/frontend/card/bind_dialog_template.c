#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

/* Forwards the target with fixed data D_80408C84 and value 6. */
s32 bind_dialog_template(struct CardDisplayNode **entries) {
    return func_80047358(entries, &D_80408C84, 6);
}
