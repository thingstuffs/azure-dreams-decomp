#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"


typedef struct S_func_800A6C4C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(void *, s32, s32);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A6C4C_0;


extern s32 classify_object_against_bounds(void *, s32);
extern void unlink_node_if_registered(void *object);

/* Clears and marks a handled object, or dispatches to its callback. */
void clear_handled_object_or_callback(S_func_800A6C4C_0 *object, s32 input, s32 callback_data) {
    s8 *status_flag;
    s32 (*callback)(void *, s32, s32);

    if (classify_object_against_bounds(object, input) != 0) {
        status_flag = object->unk_98;
        if (status_flag != 0) {
            *status_flag = 0;
        }
        unlink_node_if_registered(object);
        ((ObjectRetirementFlags *)((u8 *)object - 2))->unk_00 = (u16) (((ObjectRetirementFlags *)((u8 *)object - 2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
        return;
    }

    callback = object->unk_50;
    if (callback != 0) {
        callback(object, input, callback_data);
    }
}
