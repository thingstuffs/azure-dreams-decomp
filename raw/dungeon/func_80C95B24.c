#include "common.h"
#include "m2c_compat.h"
s32 func_800AB538(void *,void *,void *,void *);                            /* extern */

/* Delegate this action to its resident implementation. */
void func_80173324(void *state,void *position,void *render_state,void *entity) {
    func_800AB538(state,position,render_state,entity);
}
