#include "common.h"
#include "town/scene.h"
#include "town/data.h"

/* Sets the value stored in D_8001C374. */
void set_global_entry_value(s32 value) {
    scene_current_entry_value = value;
}
