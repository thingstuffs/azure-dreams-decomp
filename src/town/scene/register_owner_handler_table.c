#include "frontend/card/slot_details.h"
#include "common.h"
#include "town/scene.h"
#include "frontend/card/server_imports.h"

extern u8 D_80408D28[];
/* Bind all 21 entries of the information panel to its display template. */
s32 register_owner_handler_table(CardDevMenuEntry **entries) {
    return func_80047358(entries, D_80408D28, 0x15);
}
