#include "common.h"
#include "town/scene/hooks.h"
void func_80017A48(void *, s32);                            /* extern */

/* Pass the context and entry index to func_80017A48. */
void forward_entry_index(void *context, s32 entry_index) {
    func_80017A48(context, entry_index);
}
