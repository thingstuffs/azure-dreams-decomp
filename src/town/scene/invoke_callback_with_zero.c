/* Complete assigned cohort in retail order; compiled once as one native TU. */
#include "town/scene/invoke_callback_with_zero.h"
#include "town/scene/invoke_callback_with_zero.h"

/* Invoke the callback at offset 0x88 with zero. */
void invoke_callback_with_zero(void) {
    D_80016000->unk_20->callback_088(0);
}
