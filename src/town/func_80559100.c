#include "modules/town_ovl_4d9100.h"

/* Invokes the callback and points the shared pointer at D_800173FC. */
void func_80016100(void *callback_arg) {
    ((s32 (*)(void *))D_80016000->unk_20->callback_1F0)(callback_arg);
    D_80017494 = D_800173FC;
}
