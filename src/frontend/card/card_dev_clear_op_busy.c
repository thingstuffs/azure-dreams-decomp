#include "common.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card.h"
#include "main/data.h"

/* D_804094E8 is a dynamic/overlay-local flag word far outside this overlay's own
 * vram window and is not present in config/generated/slus_006.14.undefined_syms.txt,
 * so the generic ld -T script cannot resolve it; bind it explicitly at its real
 * linked address (narrow absolute symbol form).
 *
 * The target recomputes the address separately for the load (into v0) and the
 * store (into at) rather than caching one base register across the branch. A
 * single C reference to one symbol lets gcc's RTL CSE merge those into one
 * cached-register access, which does not match. Declaring a second alias bound
 * to the SAME real address (also via the narrow absolute-symbol form) for the
 * store gives gcc two textually distinct expressions, so it emits the two
 * separate lui/lw + lui/sw pairs the target uses. Both names resolve to the
 * identical linked address 0x804094E8; nothing is locally defined/faked. */
extern s32 card_ui_operation_state[4];

/* Clears the pending flag and returns 4 if it was set, or 0 otherwise. */
s32 card_dev_clear_op_busy(void) {
    s32 status;

    status = 0;
    if (card_ui_operation_state[0] != 0) {
        status = 4;
        D_804094E8_2[0] = 0;
    }
    return status;
}
