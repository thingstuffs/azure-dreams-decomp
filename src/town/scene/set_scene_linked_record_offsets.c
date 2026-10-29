#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"


/* Set the linked record's second and third values to 1696 and 800. */
void set_scene_linked_record_offsets(void) {
    (*(s32 **)((s8 *)town_scene_root + 0x1C))[1] = 1696;
    (*(s32 **)((s8 *)town_scene_root + 0x1C))[2] = 800;
}
