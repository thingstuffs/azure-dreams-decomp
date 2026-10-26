#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "engine/item.h"

/* extern decls */


/*
 * Resolves the low five bits of the record code when its first word is set; otherwise returns
 * primary_actor_record.
 */
int resolve_record_value(DungeonItemEntry *record)
{
    if (record->unk_00 != 0) {
        return resolve_indexed_value(record->unk_03 & 0x1F);
    }
    return ((int)primary_actor_record);
}
