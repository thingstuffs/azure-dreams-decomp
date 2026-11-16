#include "common.h"
#include "engine/menu.h"
#include "engine/item.h"
#include "slus/data.h"

/* Two-level item table lookup: itemCategoryTable[categoryIndex].kind selects whether the
 * itemCategoryTable[categoryIndex].records array (pointed to by the struct's offset0xC field)
 * is laid out as 12-byte or 20-byte records; records[recordIndex]'s signed halfword field
 * at offset 2 is then used as an index into the word table D_8007361C. */
typedef struct S_8004A658_RecA { s16 f0; s16 f1; s16 pad[4]; } S_8004A658_RecA;   /* 12-byte record, kind != 0 */
typedef struct S_8004A658_RecB { s16 f0; s16 f1; s16 pad[8]; } S_8004A658_RecB;   /* 20-byte record, kind == 0 */

/* Returns the word-table value selected by an item record in the given category. */
s32 lookup_item_category_mapped_value(s32 category_index, s32 record_index)
{
    return item_display_icon_words[(&itemCategoryTable[category_index])->record_format == 0
        ? ((S_8004A658_RecB *)(&itemCategoryTable[category_index])->records)[record_index].f1
        : ((S_8004A658_RecA *)(&itemCategoryTable[category_index])->records)[record_index].f1];
}
