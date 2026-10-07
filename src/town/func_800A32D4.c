#include "common.h"

extern void door_open_demo_set_sub(void *script_context, s32 script_arg);

/* door_open_demo_set: Run the shared town script handler with argument 8. */
void door_open_demo_set(void *script_context) {
    door_open_demo_set_sub(script_context, 8);
}
