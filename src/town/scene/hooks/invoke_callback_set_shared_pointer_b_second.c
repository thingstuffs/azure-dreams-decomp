#include "modules/town_ovl_4d9100.h"
#include "modules/town_ovl_4d9100.h"

/* Invokes the callback and points the shared pointer at D_800173FC. */
void invoke_callback_and_set_shared_pointer(void *callback_arg) {
    ((s32 (*)(void *))D_80016000->unk_20->callback_1F0)(callback_arg);
    D_80017494 = D_800173FC;
}
