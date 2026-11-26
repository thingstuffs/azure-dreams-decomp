#include "common.h"
#include "engine/sprite.h"

#include "engine/item.h"
#include "slus/data.h"
#include "town/map.h"


/* Selects a global array based on the object check and returns get_item_name_text's result. */
int get_item_name_with_fallback_pair(struct DungeonItemEntry *object)
{
    int check_result = check_required_building_slots();
    char **selected_array;

    if (check_result) {
        selected_array = item_text_checked_fallback_pair;
    } else {
        selected_array = item_text_default_fallback_pair;
    }

    return get_item_name_text(object, selected_array);
}
