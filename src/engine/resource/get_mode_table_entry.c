#include "common.h"
#include "slus/runtime_directory.h"

#include "engine/resource.h"
#include "slus/data.h"


/* Returns an indexed value from the table selected by the current mode. */
u32 get_mode_table_entry(s32 index)
{
    if (runtime_dispatch_mode_alias[0] == 2) {
        return runtime_mode_two_values[index];
    }

    return D_800D0858[index];
}
