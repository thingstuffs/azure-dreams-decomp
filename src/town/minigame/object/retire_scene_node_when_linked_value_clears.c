#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/object.h"

   /* the 0x2 bytes before arg0 in retire_scene_node_when_linked_value_clears, addressed as arg0[-1] */



/* Set record and global flags when the linked value is zero. */
void retire_scene_node_when_linked_value_clears(GymSpriteObject *record) {
    ObjectStatusPrefix16 *record_view = (ObjectStatusPrefix16 *)record;
    if (*record->link.linked_value == 0) {
        record_view[-1].flags = (u16) (record_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
