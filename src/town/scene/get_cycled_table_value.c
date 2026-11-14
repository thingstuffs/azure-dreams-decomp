#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

typedef struct {
    s32 values[3];
} ValueTable;

extern ValueTable scene_event_data;

/* Select a value from the table using the result of query 0x990. */
s32 get_cycled_table_value(void) {
    ValueTable table = scene_event_data;

    return table.values[read_script_flag_range(F_sbs34_pad16, 2)];
}
