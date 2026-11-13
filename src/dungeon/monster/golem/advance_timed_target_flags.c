#include "common.h"
#include "slus/imports.h"
#include "dungeon/monster/golem.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/monster/golem_frames.h"

typedef struct {
    s32 words[6];
} Copy24;




typedef struct S_80174D24_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D24_1;   /* arg1 in advance_timed_target_flags */

typedef struct S_80174D24_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80174D24_4;   /* ((CopiedRenderObjectBody *)arg0)->render_data */

/* Copies object data with offsets and advances a timed target flag cycle. */
void advance_timed_target_flags(CopiedRenderObjectBody *state, void *output_arg, SpriteFrameState *target)
{
    S_80174D24_1 *output = output_arg;
    GteOffset offsets;
    SpriteFrameState *object;
    Copy24 *source;
    s32 copy_word_a;
    s32 copy_word_b;
    s32 offset_mode;
    struct SpriteAttachment *object_id;
    s32 phase;
    u16 old_ticks;
    s32 signed_ticks;
    u16 target_flags;

    if (((S_80174D24_4 *)state->render_data)->unk_2C != golem_frame_set_3) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    source = state->source_state;
    *(Copy24 *)output = *source;

    object = state->render_data;
    offset_mode = 0;
    object_id = object->source;
    if (resolve_record_orientation_or_fallback(object_id, object,
                      &offsets.orientation, offset_mode) != 0) {
        output->unk_00.at02.v += offsets.distance[0];
        output->unk_04.at02.v += offsets.distance[1];
        output->unk_08.at02.v += offsets.distance[2];
    }

    old_ticks = state->frames;
    phase = state->phase.s;
    copy_word_a = old_ticks + 1;
        state->frames = copy_word_a;

    switch (phase) {
    case 0:
        advance_sprite_animation_and_textures(target);
        target_flags = target->flags;
        if ((target_flags & 0x6000) == 0) {
            return;
        }
        target->flags = target_flags | 0x80;
        state->frames = 0;
        state->phase.u++;
        break;
    case 1:
        signed_ticks = (s16)copy_word_a;
        if (signed_ticks < 0x40) {
            return;
        }
        target->flags &= 0xFF7F;
        select_sprite_entry(target, 0x38, 0);
        state->frames = 0;
        state->phase.s = 0;
        break;
    }
}

/* MECHANISM: True-space epilogue joins and a u16[3] output object produce the 0x28 frame. Ordering
   mode_zero before mode_one removes the word-61 displacement cascade. */
