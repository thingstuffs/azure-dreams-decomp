#include "modules/dungeon_ovl_1831370.h"

s32 dungeonAdjustSelectionByItemCount(s32 input_value, s32 target, s32 lookup_index)
{
    return advanceIndexWithSingleWrap(target, input_value, D_800294F8[lookup_index]);
}
