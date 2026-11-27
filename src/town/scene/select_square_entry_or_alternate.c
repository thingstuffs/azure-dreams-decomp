#include "town/scene.h"
#include "town/scene/motion.h"
extern u8 town_map_square_entry_response_entries[];
extern u8 town_map_square_alternate_response[];
extern u8 D_8001C354[];
extern s32 resolve_entry_second_flag(void *, void *, s32);

void *select_square_entry_or_alternate(TownObjectSet *entry, s32 unused, s32 selection) {
    void *records = town_map_square_entry_response_entries;
    void *result;
    void *selected;
    result = apply_entry_position(records, D_8001C354, entry, selection);
    if (resolve_entry_second_flag(records, entry, selection) == 0) {
        selected = result;
    } else {
        selected = town_map_square_alternate_response;
    }
    return selected;
}
