#include "common.h"

#include "common.h"
void func_8003B034(void);                            /* extern */
void func_8003B06C(void);                            /* extern */
void plt_init_sleep_set(void);                            /* extern */

/* Runs the three runtime routines in sequence. */
void func_8003B1B4(void) {
    func_8003B034();
    func_8003B06C();
    plt_init_sleep_set();
}
