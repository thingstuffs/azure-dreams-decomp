#include "common.h"
#include "m2c_compat.h"
s32 func_800ABDBC(void *,void *,void *,void *);                                /* extern */
extern void func_8017102C(void *,void *,void *,void *);


typedef struct S_80173364_0 {
    u8 pad_00[0x8C];
    void (*handler)(void *,void *,void *,void *);
} S_80173364_0;   /* state in func_80173364 */

/* Run this action and restore the main state handler when it completes. */
void func_80173364(S_80173364_0 *state,void *position,void *render_state,void *entity) {
    if (func_800ABDBC(state,position,render_state,entity) != 0) {
        state->handler = func_8017102C;
    }
}
