#include "common.h"
#include "m2c_compat.h"
s32 func_800AC480(void *,void *,void *,void *);                                /* extern */
extern void func_8017102C(void *,void *,void *,void *);


typedef struct S_80173B64_0 {
    u8 pad_00[0x8C];
    void (*handler)(void *,void *,void *,void *);
} S_80173B64_0;   /* state in func_80173B64 */

/* Run this action and restore the main state handler when it completes. */
void func_80173B64(S_80173B64_0 *state,void *position,void *render_state,void *entity) {
    if (func_800AC480(state,position,render_state,entity) != 0) {
        state->handler = func_8017102C;
    }
}
