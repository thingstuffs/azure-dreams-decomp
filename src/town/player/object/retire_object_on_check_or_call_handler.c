#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "town/menu.h"
#include "town/player/object.h"


typedef struct S_func_800A6C4C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(void *, ObjectPosition *, s32);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A6C4C_0;

/* Clears and marks a handled object, or dispatches to its callback. */
void retire_object_on_check_or_call_handler(S_func_800A6C4C_0 *object, ObjectPosition *position, s32 callback_data) {
    s8 *status_flag;
    s32 (*callback)(void *, ObjectPosition *, s32);

    if (classify_object_against_bounds(object, position) != 0) {
        status_flag = object->unk_98;
        if (status_flag != 0) {
            *status_flag = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        return;
    }

    callback = object->unk_50;
    if (callback != 0) {
        callback(object, position, callback_data);
    }
}
