#include "common.h"
#include "town/map/effect.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/scene/object.h"

/* Process a record with a zero status byte and set its header and global flags. */
void retire_record_when_status_clear(void *record_arg) {
    MapParticleEffect *effect = record_arg;

    if (*effect->active_flag == 0) {
        unlink_scene_list_node(record_arg);
        unlink_node_if_registered(record_arg);
        NODE_HEADER(record_arg)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
