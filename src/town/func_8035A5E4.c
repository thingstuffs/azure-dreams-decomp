#include "modules/town_ovl_2da5e4.h"

/* Invoke the callback at offset 0x88 with zero. */
void invoke_callback_with_zero(void) {
    D_80016000->unk_20->callback_088(0);
}
