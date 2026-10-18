#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"

typedef struct {
    u8 index;
    u8 group;
} DungeonArg;



extern void item_clear_recorded_category_pair(u8, u8);

/* Updates the selected item through item_clear_recorded_category_pair and clears its flag 0x400 in the item category table. */
void clear_selected_item_flag_400(DungeonArg *selection)
{
    item_clear_recorded_category_pair(selection->group, selection->index);
    D_80073414[selection->group].entries[selection->index].flags &= 0xFBFF;
}
