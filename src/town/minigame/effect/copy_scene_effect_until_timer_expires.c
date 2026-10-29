#include "common.h"
#include "shared/object_flags.h"
#include "slus.h"

typedef struct {
    s32 words[6];
} CopyRecord;

/* Copies an entry's record, decrements its count, and flags exhaustion. */
void copy_scene_effect_until_timer_expires(u8 *entry, CopyRecord *out_record, void *update_arg)
{
    CopyRecord *source_record;
    u16 remaining;

    advance_sprite_animation_and_textures(update_arg);
    source_record = *(CopyRecord **)(entry + 4);
    *out_record = *source_record;

    remaining = *(u16 *)(entry + 2) - 1;
    *(u16 *)(entry + 2) = remaining;
    if ((remaining << 16) <= 0) {
        *(u16 *)(entry - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
