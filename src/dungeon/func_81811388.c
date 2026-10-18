#include "modules/dungeon_ovl_1831370.h"

s32 adjust_selection_by_item_count(s32 input_value, s32 target, s32 lookup_index)
{
    return advance_index_with_single_wrap(target, input_value, D_800294F8[lookup_index]);
}
