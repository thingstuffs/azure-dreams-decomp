#include "modules/town_door.h"

/* door_open_demo_set: Run the shared town script handler with argument 8. */
void door_open_demo_set(s32 script_context) {
    door_open_demo_set_sub(script_context, 8);
}
