#include "common.h"
#include "town/scene/choice_data.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/data.h"

/* Returns the table entry selected by the current index. */
s32 get_indexed_table_entry(void) {
    return scene_choice_values[scene_choice_index];
}
