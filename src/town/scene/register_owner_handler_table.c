#include "common.h"
#include "town/scene.h"
#include "frontend/card/server_imports.h"

extern u8 D_80408D28[];
/* Calls func_80047358 with owner, D_80408D28, 0x15. */
void register_owner_handler_table(void *owner) { func_80047358(owner, D_80408D28, 0x15); }
