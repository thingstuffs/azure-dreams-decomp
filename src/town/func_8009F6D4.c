#include "modules/town_town_windows.h"

/* Create a record, assign its handler, and run the remaining initialization routines. */
void func_8009CE34(void) {
    ((func_8009F6D4_S_8009CE34_0 *)(initialize_scene_object_in_buffer(0x11, &D_801006D0, 0x49)))->unk_10 = &build_entries_and_update_state;
    dispatch_parameterized_or_default(&D_80100900);
    update_map_world_extents();
}
