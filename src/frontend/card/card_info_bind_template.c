#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

extern M2C_UNK D_80408D28;

/* Forwards value to func_80047358 with D_80408D28 and constant 0x15. */
s32 card_info_bind_template(struct CardDevMenuEntry **entries) {
    return func_80047358(entries, &D_80408D28, 0x15);
}
