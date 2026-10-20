#include "common.h"
#include "shared/object_flags.h"

extern s32 classify_object_against_bounds(void *, void *);
extern void unlink_scene_list_node(void *node);
extern void unlink_node_if_registered(void *object);

typedef struct S_func_800BB508_0 {
    u8 pad_00[0x98];
    void *unk_98;
} S_func_800BB508_0;

/* On a successful object check, clear its linked byte and set object and global flags. */
void clear_object_link_and_mark_complete(S_func_800BB508_0 *object, void *context) {
    if (classify_object_against_bounds(object, context) != 0) {
        unlink_scene_list_node(object);
        if (object->unk_98 != 0) {
            *(s8 *)object->unk_98 = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
