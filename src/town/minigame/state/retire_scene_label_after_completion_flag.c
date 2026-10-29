#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/state.h"


/* Set object and global flags when the state is zero and linked bit 1 is set. */
void retire_scene_label_after_completion_flag(void *object) {
    void *linked_data = *(void **)((u8 *)object + 0xC);

    if (*(s16 *)object == 0 &&
        (*(u16 *)((u8 *)linked_data + 0xC) & 2) != 0) {
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
