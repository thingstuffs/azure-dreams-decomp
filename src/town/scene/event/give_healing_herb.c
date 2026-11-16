#include "common.h"
#include "town/scene/event.h"
#include "town/shop/object.h"

/* Submit command 8 with its flag set and remaining arguments cleared. */
void give_healing_herb(void) {
    s8 command_args[4];

    command_args[1] = 1;
    command_args[0] = 8;
    command_args[2] = 0;
    command_args[3] = 0;
    append_town_item(command_args);
}
