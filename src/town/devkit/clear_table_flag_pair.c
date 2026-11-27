#include "common.h"
#include "town/data.h"
#include "town/scene/flags.h"
#include "town/devkit.h"
extern DevkitFlagPair D_80700638[];

/* Clear the source and target flags of the pair entries from 1 up to 2 (the loop runs once). */
void clear_table_flag_pair(void) {
    s32 index;

    index = 1;
    do {
        clear_indexed_flag_bit_unless_index_one_80700d20(D_80700638[index].source);
        clear_indexed_flag_bit_unless_index_one_80700d20(D_80700638[index].target);
        index++;
    } while (index < 2);
}
