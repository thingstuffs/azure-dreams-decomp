#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad0[0x1A];
    u16 flags;
} S_8081CB78_sub;

typedef struct {
    s16 state;
    u8 pad2[0xA];
    S_8081CB78_sub *sub;
} S_8081CB78;


/* Set object and global flags when the state is zero and subobject bit 3 is set. */
void retire_scene_label_after_exit_flag(S_8081CB78 *object) {
    s16 state = object->state;
    S_8081CB78_sub *sub = object->sub;

    if (state == 0 && (sub->flags & 8)) {
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
