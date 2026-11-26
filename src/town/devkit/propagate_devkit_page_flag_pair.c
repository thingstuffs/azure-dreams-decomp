#include "common.h"
#include "town/devkit.h"
#include "town/scene/flags.h"

extern s16 D_80700BA4[];
extern s16 D_80700BAC[];

/* Copy the page's first flag into its second flag, then set the first flag. */
void propagate_devkit_page_flag_pair(s32 index)
{
    if (test_indexed_flag_bit(D_80700BA4[index]) != 0) {
        set_indexed_flag_bit(D_80700BAC[index]);
    } else {
        clear_indexed_flag_bit(D_80700BAC[index]);
    }
    set_indexed_flag_bit(D_80700BA4[index]);
}
