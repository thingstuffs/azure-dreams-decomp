#include "common.h"
#include "town/data.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/scene/flags.h"
#include "town/shop/state.h"

extern DevkitFlagPair D_80700638[];

/* Copy the entry's source flag into its target flag, then set the source flag. */
void propagate_devkit_entry_flag_pair(s32 index)
{
    if (test_indexed_flag(D_80700638[index].source) != 0) {
        set_linked_flag_80700cd0(D_80700638[index].target);
    } else {
        clear_indexed_flag_bit_unless_index_one_80700d20(D_80700638[index].target);
    }
    set_linked_flag_80700cd0(D_80700638[index].source);
}
