#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

typedef struct {
    s32 values[3];
} ValueTable;

extern ValueTable scene_event_data;
extern s32 func_80018868(s32, s32);

/* Select a value from the table using the result of query 0x990. */
s32 select_table_query(void) {
    ValueTable table = scene_event_data;

    return table.values[func_80018868(F_sbs34_pad16, 2)];
}
