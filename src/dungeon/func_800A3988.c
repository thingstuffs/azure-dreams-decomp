#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "common.h"

typedef struct {
    u8 index;
    u8 group;
} DungeonArg;



extern void itemClearRecordedCategoryPair(u8, u8);

/* Updates the selected item through itemClearRecordedCategoryPair and clears its flag 0x400 in the item category table. */
void clearSelectedItemFlag400(DungeonArg *selection)
{
    itemClearRecordedCategoryPair(selection->group, selection->index);
    D_80073414[selection->group].entries[selection->index].flags &= 0xFBFF;
}
