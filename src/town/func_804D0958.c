#include "modules/town_ovl_450958.h"

/* Select D_800174BC and invoke the state callback with zero. */
void func_80016158(void) {
    D_8001758C = D_800174BC;
    D_80016000->unk_20->callback_190(0);
}
