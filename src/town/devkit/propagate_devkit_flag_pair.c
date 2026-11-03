#include "common.h"
#include "town/devkit.h"
#include "town/shop/state.h"
#include "town/scene/flags.h"
#include "town/data.h"

/* Propagate the first table's flag to the second table's flag, then set the first. */
void propagate_devkit_flag_pair(s32 index) {
    if (test_linked_flag_80700dc0(D_A0700F1C[index]) != 0) {
        set_linked_flag_80700d1c(D_A0700F24[index]);
    } else {
        clear_indexed_flag_bit_unless_index_one(D_A0700F24[index]);
    }
    set_linked_flag_80700d1c(D_A0700F1C[index]);
}
