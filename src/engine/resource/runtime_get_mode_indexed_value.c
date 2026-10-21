#include "common.h"

#include "common.h"
#include "engine/resource.h"
#include "slus/data.h"

extern unsigned char runtime_dispatch_mode_alias[9];

/* Returns an indexed value from the table selected by the current mode. */
u32 runtime_get_mode_indexed_value(s32 index)
{
    if (runtime_dispatch_mode_alias[0] == 2) {
        return runtime_mode_two_values[index];
    }

    return D_800D0858[index];
}
