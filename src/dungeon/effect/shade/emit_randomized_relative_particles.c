#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800D5294_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D5294_5;

typedef struct S_800D5294_0_pre {
    u16 unk_00;
} S_800D5294_0_pre;   /* the 0x2 bytes before arg0 in emit_randomized_relative_particles, addressed as arg0[-1] */

typedef struct S_800D5294_2 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D5294_2;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 rand();                                /* extern */
void initialize_effect_object_state(); /* extern */
extern M2C_UNK D_800D50FC[3];

/* Emit randomized particles at the parent-relative position and expire the emitter when its lifetime ends. */
void emit_randomized_relative_particles(void *emitter, Rec_func_800D4BD4_arg2 *position, M2C_UNK spawn_context) {
    s32 particle_index;
    u16 tick_or_offset;
    u16 life_left;
    s16 coord;
    s16 particle_size;
    S_800D5294_5 *parent;
    ObjectPosition *particle_motion;
    M2C_UNK *particle_data;
    ObjectNodeHeader *particle;
    S_800D5294_2 *particle_state;

    parent = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_24;
    position->unk_02.as_s16 = (s16) (((MovingPosition *)(parent->unk_08))->unk_02
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3C);
    position->unk_06.as_s16 = (s16) (((MovingPosition *)(parent->unk_08))->unk_06
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3E);
    position->unk_0A.as_s16 = (s16) (((MovingPosition *)(parent->unk_08))->unk_0A
        + ((Rec_func_800D4BD4_arg1 *)emitter)->unk_40);
    tick_or_offset = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 = tick_or_offset;
    if ((s16) tick_or_offset < 0x14) {
        particle_index = 0;
        particle_size = 0x20;
        particle_data = D_800D50FC;
        do {
            particle = allocate_flagged_object_node(0x212);
            if (particle != NULL) {
                initialize_effect_object_state(particle, emitter, position, spawn_context);
                particle_state = ((void *)particle) + 0x20;
                particle_state->unk_1E = particle_size;
                particle_state->unk_20 = particle_size;
                particle->unk_10 = particle_data;
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
        ((S_800D5294_0_pre *)emitter)[-1].unk_00 = (u16) (((S_800D5294_0_pre *)emitter)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    }
}
