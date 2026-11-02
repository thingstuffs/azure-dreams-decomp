#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

/* Forwards the target with fixed data D_80408C84 and value 6. */
void bind_dialog_template(s32 target) {
    func_80047358(target, &D_80408C84, 6);
}
