#include "shared/entity.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/emit_particles_until_expired.h"

struct ObjectNodeHeader;
#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

#ifndef NULL
#define NULL 0
#endif



typedef struct S_800D4DE8_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800D4DE8_8;   /* ((Rec_func_800D4BD4_arg1 *)arg0)->unk_00 in emit_particles_until_expired */

/* Emit particles around the parent position and retire the emitter when its lifetime expires. */
void emit_particles_until_expired(void *emitter, Rec_func_800D4BD4_arg2 *position, s32 init_param) {
    s32 particle_index;
    u16 age;
    u16 life_left;
    ObjectNodeHeader *parent;
    ObjectPosition *particle_motion;
    ObjectNodeHeader *particle;
    FadingMotionParticleBody *particle_state;

    parent = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_24;
    position->unk_02.as_s16 =
        (s16)(parent->position->x.unsigned_parts.integer +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3C);
    position->unk_06.as_s16 =
        (s16)(parent->position->y.unsigned_parts.integer +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3E);
    position->unk_0A.as_s16 =
        (s16)(parent->position->z.unsigned_parts.integer +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_40);
    age = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 = age;
    if ((s16)age < 0x14) {
        particle_index = 0;
        do {
            particle = allocate_flagged_object_node(0x212);
            if (particle != NULL) {
                initialize_effect_object_state(particle, emitter, position, init_param);
                particle_state = NODE_BODY(particle);
                particle_state->remaining_ticks = 0xA;
                particle_state->initial_ticks = 0xA;
                particle->update_callback = advance_damped_effect_motion;
                particle_motion = particle->position;
                particle_motion->velocity_x =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->velocity_y =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->velocity_z =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->z.w.i =
                    (u16)particle_motion->z.w.i -
                    (entity_height_offsets[((S_800D4DE8_8 *)(((Rec_func_800D4BD4_arg1 *)emitter)->unk_00))->unk_13] >> 1);
            }
            particle_index += 1;
        } while (particle_index < 4);
    }
    life_left = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E - 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        NODE_HEADER(emitter)->flags = NODE_HEADER(emitter)->flags | 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    }
}
