#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity.h"
#include "shared/slus_callbacks.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "dungeon/monster/cyclone.h"
#include "slus.h"

typedef struct S_80175060_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80175060_1;

/* Creates an object with randomized phase and rotation and copies its initial state. */
/* Creates a gray effect at the owner's height with randomized rotation and phase, preserving the initial
 * motion origin. */
void * create_randomized_motion_object(ActorRecord *owner, ObjectPosition *initial_state) {
    s32 color;
    s32 four;
    s32 phase_rand;
    s32 rotation_rand;
    s32 biased_phase;
    s32 biased_rotation;
    S_80175060_1 *part;
    ObjectNodeHeader *object;
    ObjectPosition *state;
    u16 height;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->update_callback = &update_radial_motion_or_complete;
        biased_phase = rand();
        phase_rand = biased_phase;
        part = ((void *)object) + 0x20;
        if (phase_rand < 0) {
            biased_phase = phase_rand + 0xFFF;
        }
        color = 0x606060;
        part->unk_04 = (s16) (phase_rand - ((biased_phase >> 0xC) << 0xC));
        four = 4;
        part->unk_08 = (s16) four;
        part = object->sprite;
        part->unk_0C = color;
        part->unk_14 = (u16) (part->unk_14 | 0xC);
        part->unk_10 = (u16) (part->unk_10 | 0x20);
        select_record_entry_and_value(part, &secondary_sprite, 0);
        advance_sprite_animation_and_textures(part);
        biased_rotation = rand();
        rotation_rand = biased_rotation;
        part->unk_1A = (s16) (rotation_rand % 4096);
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        register_node(object, project_sprite_chain);
        {
            s32 copy_word_1;

            state = object->position;
            *state = *initial_state;
            copy_word_1 = state->y.v;
            state->velocity_x = state->x.v;
            state->velocity_y = copy_word_1;
        }
        height = owner->ground_height;
        state->z.w.i = height;
        return object;
    }
    return 0;
}

