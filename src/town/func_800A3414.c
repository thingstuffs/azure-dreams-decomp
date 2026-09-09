#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK change_map();
extern s32 get_player_homerank();
extern M2C_UNK func_800B28A0();

/* Changes maps using direct map data or a selected table entry. */
void func_800A0B74(void *map_source, s32 *map_table) {
    u8 selection_mode;

    selection_mode = *((u8 *)((s8 *)map_source + 0x96));
    if (selection_mode == 0) {
        map_source = map_table;
    } else {
        s32 map_index;

        if (selection_mode == 1) {
            map_index = func_800B28A0();
        } else {
            map_index = get_player_homerank();
        }
        map_source = (void *)map_table[map_index];
    }
    change_map(map_source);
}
