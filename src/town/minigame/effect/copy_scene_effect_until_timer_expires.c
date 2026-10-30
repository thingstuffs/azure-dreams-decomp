#include "common.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "town/minigame/effect.h"

/* Copies an entry's record, decrements its count, and flags exhaustion. */
void copy_scene_effect_until_timer_expires(SceneEffectCopyObject *entry, CopyRecord *out_record, void *update_arg)
{
    CopyRecord *source_record;
    u16 remaining;

    advance_sprite_animation_and_textures(update_arg);
    source_record = entry->source;
    *out_record = *source_record;

    remaining = entry->timer.u - 1;
    entry->timer.u = remaining;
    if ((remaining << 16) <= 0) {
        ((u16 *)entry)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
