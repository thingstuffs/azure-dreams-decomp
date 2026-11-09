#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/menu.h"
#include "town/map.h"


typedef struct S_func_800A9624_1 {
    u8 pad_00[0x50];
    s32 (*unk_50)(void *, s32, s32);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A9624_1;

struct TownPositionXY; void write_square_position_offsets(s16, s16, s16, s16, struct TownPositionXY *);


/* Process object state results or invoke the fallback callback. */
void process_object_state_or_fallback(S_func_800A9624_1 *object, s32 state_arg, s32 callback_arg) {
    s32 state;
    s32 (*callback)(void *, s32, s32);

    state = classify_record_by_state_and_position(object, state_arg);
    if (state == 1) {
        write_square_position_offsets(0x1B, 0x1C, 0x1D, 0x1E, (struct TownPositionXY *)(state_arg));
        if (object->unk_98 != 0) {
            *object->unk_98 = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (state == 2) {
        unlink_node_if_registered(object);
        return;
    }
    register_node_if_unregistered(object, (process_linked_record_values));
    callback = object->unk_50;
    if (callback != 0) {
        callback(object, state_arg, callback_arg);
    }
}
