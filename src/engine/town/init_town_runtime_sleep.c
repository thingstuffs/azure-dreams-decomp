#include "common.h"

#include "common.h"
void func_8003B034(void);                            /* extern */
void init_town_runtime_objects(void);                            /* extern */
void plt_init_sleep_set(void);                            /* extern */

/* Runs the three runtime routines in sequence. */
void init_town_runtime_sleep(void) {
    func_8003B034();
    init_town_runtime_objects();
    plt_init_sleep_set();
}
