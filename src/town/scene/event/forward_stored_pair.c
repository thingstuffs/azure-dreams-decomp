#include "common.h"
#include "town/scene/event.h"
#include "town/data.h"
#include "town/scene/flags.h"

extern s32 D_80018E48;

/* Pass the two global values to func_80017BA0. */
void forward_stored_pair(void) {
    set_indexed_entry_flag(scene_stored_first_value, D_80018E48);
}
