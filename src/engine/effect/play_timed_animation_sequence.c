#include "engine/effect/cd_sequence.h"
#include "common.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "slus/data.h"

/* Plays timed entity animations, then flags the sequence and its entities for cleanup. */
void play_timed_animation_sequence(CdCueSequenceBody *sequence)
{
    s16 *state_ptr;
    u16 elapsed_ticks;
    s16 entity_slot;
    CdCueSequenceChildNode *entity;
    CdCueSequenceChildNode *anim_entity;
    CdCueSequenceChildBody *anim;
    CdCueSequenceFrame *frame;
    s16 next_tick;
    int entity_index;
    s32 cleanup_flags;

    elapsed_ticks = sequence->timer + 1;
    sequence->timer = elapsed_ticks;
    switch (sequence->state) {
    case 0:
        if (sequence->trigger != 0) {
            sequence->trigger = 0;
            sequence->timer = 0;
            sequence->state = sequence->state + 1;
        }
        break;

    case 1:
        if (sequence->frame->tick == ((s16) elapsed_ticks)) {
            do {
                entity_slot = (sequence->slot_index + 1) % 16;
                sequence->slot_index = entity_slot;
                anim_entity = sequence->children[entity_slot];
                anim = &anim_entity->body;
                if (anim->activation_state == 0) {
                    anim->activation_state = 1;
                    anim->x = sequence->frame->x - 0x180;
                    anim->line_x = sequence->frame->x - 0x180;
                    anim->y = sequence->frame->y;
                    anim->line_width = (sequence->frame->line_units * 12) + 12;
                    clear_and_draw_paired_text_rows(sequence->slot_index, sequence->frame);
                }
                frame = sequence->frame;
                sequence->frame = frame + 1;
                next_tick = frame[1].tick;
                if (next_tick == 0) {
                    sequence->timer = 0;
                    sequence->state = (*(state_ptr = &sequence->state)) + 1;
                    return;
                }
            }
            while (next_tick == ((s16) sequence->timer));
        }
        break;

    case 2:
        if (((s16) elapsed_ticks) >= 0x190) {
            sequence->owner->group_word = 0;
            sequence->owner->completion_count = sequence->owner->completion_count + 1;
            for (entity_index = 0; entity_index < 0x10; entity_index++) {
                entity = sequence->children[entity_index];
                cleanup_flags = D_800814A0_loop | 0x8000;
                D_800814A0_loop = cleanup_flags;
                entity->header.flags |= 0x8000;
            }

            *((u16 *) (((u8 *) sequence) - 2)) |= 0x8000;
            D_800814A0_tail = cleanup_flags;
        }
        break;
    }
}
