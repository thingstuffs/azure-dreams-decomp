#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in retire_scene_node_when_linked_value_clears, addressed as arg0[-1] */

typedef struct S_80024070_0 {
    u8 pad_00[0xC];
    s16 * unk_0C;
} S_80024070_0;   /* arg0 in retire_scene_node_when_linked_value_clears */


/* Set record and global flags when the linked value is zero. */
void retire_scene_node_when_linked_value_clears(void *record) {
    ObjectStatusPrefix16 *record_view = record;
    if (*((S_80024070_0 *)record)->unk_0C == 0) {
        record_view[-1].unk_00 = (u16) (record_view[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
