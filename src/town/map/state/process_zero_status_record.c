#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_links.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/scene/object.h"

   /* the 0x2 bytes before arg0 in process_zero_status_record, addressed as arg0[-1] */

extern struct { s32 v; s32 pad[2]; } object_flag_block;

/* Process a record with a zero status byte and set its header and global flags. */
void process_zero_status_record(void *record_arg) {
    ObjectRetirementFlags *record = record_arg;

    if (*((Rec_D_80082D58 *)record)->unk_98.as_pu8 == 0) {
        unlink_scene_list_node(record_arg);
        unlink_node_if_registered(record);
        record[-1].flags = (u16) (record[-1].flags | 0x8000);
        object_flag_block.v |= 0x8000;
    }
}
