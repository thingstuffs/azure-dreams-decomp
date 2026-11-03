#include "common.h"
#include "town/scene/flags.h"
#include "town/devkit.h"
extern s32 D_80700A18[];

/* Run the indexed operation and return its table value. */
s32 grid_run_indexed_operation_a(s32 table_index, s32 call_input, s32 call_param, s32 call_extra) {
    dispatch_entry_flags_80700c54(table_index);
    return D_80700A18[table_index];
}
