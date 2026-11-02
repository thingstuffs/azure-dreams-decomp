#include "engine/effect/cd_sequence.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "slus/data.h"



/* Sub-object embedded at offset 0x20 of the entity (same family as
 * init_color_fade_effect / init_fade_in_out_effect): owner backpointer, four zeroed shorts,
 * a table pointer, then a walked slot array of s32 (16 entries, +4/step). */
struct S_8005313C;

extern void init_shaded_line_effect(void *a0, s16 a1);

/* Initializes the entity state and sub-object, creates up to 16 slots, and initializes the global table. */
void scene_initialize_sixteen_sprite_sequence(CdCueSequenceNode *entity, void *owner)
{
    CdCueSequenceBody *body;
    s32 slot_index;

    void *slot;

    slot_index = 0;
    body = &entity->body;
    entity->header.update_callback = play_timed_animation_sequence;
    body->owner = owner;
    body->state = 0;
    body->timer = 0;
    body->slot_index = 0;
    body->trigger = 0;
    body->frame = (CdCueSequenceFrame *)&sixteen_sprite_sequence_source;

    do {
        slot = allocate_list_node(0x212, &entity->header.next);
        if (slot != 0) {
            init_shaded_line_effect(slot, (s16)slot_index);
            body->children[slot_index] = slot;
        }
        slot_index++;
    } while (slot_index < 0x10);

    init_sixteen_packed_templates();
}
