#include "modules/town_door.h"

/* Changes maps using direct map data or a selected table entry. */
void change_door_map(void *map_source, s32 *map_table) {
    u8 selection_mode;

    selection_mode = *((u8 *)((s8 *)map_source + 0x96));
    if (selection_mode == 0) {
        map_source = map_table;
    } else {
        s32 map_index;

        if (selection_mode == 1) {
            map_index = find_target_byte_index_in_list();
        } else {
            map_index = get_player_homerank();
        }
        map_source = (void *)map_table[map_index];
    }
    change_map(map_source);
}
