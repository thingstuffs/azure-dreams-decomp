#include "common.h"
#include "m2c_compat.h"
s32 func_800AD058(void *,void *,void *,void *);                            /* extern */

/* Delegate this action to its resident implementation. */
void func_80173304(void *state,void *position,void *render_state,void *entity) {
    func_800AD058(state,position,render_state,entity);
}
