#include "shared/object_node.h"
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 D_800A5D5C;


/* Set the object data pointer and increment the global state counter. */
void create_timed_status_object(void) {

    ((s32 **)func_8003FC64(0))[4] = &D_800A5D5C;
    g_dungeon_status.unk_0A += 1;
}
