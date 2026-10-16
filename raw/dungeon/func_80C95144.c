#include "common.h"
#include "m2c_compat.h"
s32 func_800AB378(void *,void *,void *,void *);                                /* extern */
s32 func_800AD9B4(void *,void *);                /* extern */
extern void func_8017102C(void *,void *,void *,void *);


typedef struct S_80172944_0 {
    u8 pad_00[0x8C];
    void (*handler)(void *,void *,void *,void *);
} S_80172944_0;   /* state in func_80172944 */

/* Run this action and restore the main state handler after completion. */
void func_80172944(S_80172944_0 *state,void *position,void *render_state,void *entity) {
    if ((func_800AB378(state,position,render_state,entity) != 0) && ((func_800AD9B4(render_state, entity) << 0x10) > 0)) {
        state->handler = func_8017102C;
    }
}
