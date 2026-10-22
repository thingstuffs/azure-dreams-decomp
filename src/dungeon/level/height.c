#include "dungeon/level.h"

/* Selector hook called before dispatching a banked callback.
 * The shipped implementation ignores the incoming selector and returns immediately.
 * Two registered direct JAL callers establish this entry; no accounting stub is inferred. */
void bank_selector_no_op(s32 selector)
{
}
