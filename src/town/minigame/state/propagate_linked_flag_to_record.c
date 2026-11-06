#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/state.h"

typedef struct S_80020468_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80020468_2;   /* ((S_80020468_1 *)arg0)->unk_04 in propagate_linked_flag_to_record */


   /* arg0 in propagate_linked_flag_to_record; pointer addresses record offset 0x2 */


/* Propagate bit 15 from the linked record to the record and global flags. */
void propagate_linked_flag_to_record(SceneTileObject *record) {
    if (((S_80020468_2 *)(record->linked))->unk_04 & 0x8000) {
        NODE_HEADER(record)->flags = (u16) (NODE_HEADER(record)->flags
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
