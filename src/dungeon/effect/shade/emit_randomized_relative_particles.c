#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "dungeon/effect/shade_callbacks_api.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/emit_particles_until_expired.h"



/* cfail-repair: tf7-phase1-cache-v3 */

/* Emit randomized particles at the parent-relative position and expire the emitter when its lifetime ends. */
void emit_randomized_relative_particles(void *emitter, Rec_func_800D4BD4_arg2 *position, M2C_UNK spawn_context) {
    s32 particle_index;
    u16 tick_or_offset;
    u16 life_left;
    s16 coord;
    s16 particle_size;
    ObjectNodeHeader *parent;
    ObjectPosition *particle_motion;
    M2C_UNK *particle_data;
    ObjectNodeHeader *particle;
    FadingMotionParticleBody *particle_state;

    parent = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_24;
    position->unk_02.as_s16 = (s16) (parent->position->x.unsigned_parts.integer
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3C);
    position->unk_06.as_s16 = (s16) (parent->position->y.unsigned_parts.integer
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3E);
    position->unk_0A.as_s16 = (s16) (parent->position->z.unsigned_parts.integer
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_40);
    tick_or_offset = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 = tick_or_offset;
    if ((s16) tick_or_offset < 0x14) {
        particle_index = 0;
        particle_size = 0x20;
        particle_data = update_effect_motion_and_color;
        do {
            particle = allocate_flagged_object_node(0x212);
            if (particle != NULL) {
                initialize_effect_object_state(particle, emitter, position, spawn_context);
                particle_state = NODE_BODY(particle);
                particle_state->remaining_ticks = particle_size;
                particle_state->initial_ticks = particle_size;
                particle->update_callback = particle_data;
                particle_motion = particle->position;
                tick_or_offset = rand() & 0x3F;
                coord = particle_motion->x.w.i;
                coord = coord - 0x1F;
                particle_motion->x.w.i = coord + tick_or_offset;
                tick_or_offset = rand() & 0x3F;
                coord = particle_motion->y.w.i;
                coord = coord - 0x1F;
                particle_motion->y.w.i = coord + tick_or_offset;
                tick_or_offset = rand() & 0x1F;
                particle_motion->z.w.i = (s16) (particle_motion->z.w.i - tick_or_offset);
                particle_motion->velocity_z = (s32) ((0 - ((rand() & 0xFFFF) + 0x10000)) * 2);
            }
            particle_index += 1;
        } while (particle_index < 4);
    }
    life_left = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E - 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        NODE_HEADER(emitter)->flags = (u16) (NODE_HEADER(emitter)->flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    }
}
