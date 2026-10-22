#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D4DE8_0_pre {
    u16 unk_00;
} S_800D4DE8_0_pre;   /* the 0x2 bytes before arg0 in emit_particles_until_expired, addressed as arg0[-1] */


typedef struct S_800D4DE8_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D4DE8_2;

typedef struct S_800D4DE8_3 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D4DE8_3;

typedef struct S_800D4DE8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800D4DE8_4;

typedef struct S_800D4DE8_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4DE8_5;

typedef struct S_800D4DE8_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D4DE8_6;   /* global in emit_particles_until_expired */



typedef struct S_800D4DE8_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800D4DE8_8;   /* ((Rec_func_800D4BD4_arg1 *)arg0)->unk_00 in emit_particles_until_expired */


extern s32 rand(void);
extern void initialize_effect_object_state(void *, void *, void *, s32);
extern u8 D_800D4CB0[];

/* Emit particles around the parent position and retire the emitter when its lifetime expires. */
void emit_particles_until_expired(void *emitter, Rec_func_800D4BD4_arg2 *position, s32 init_param) {
    s32 particle_index;
    u16 age;
    u16 life_left;
    S_800D4DE8_2 *parent;
    S_800D4DE8_5 *particle_motion;
    void *particle;
    S_800D4DE8_3 *particle_state;

    parent = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_24;
    position->unk_02.as_s16 =
        (s16)(((MovingPosition *)(parent->unk_08))->unk_02 +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3C);
    position->unk_06.as_s16 =
        (s16)(((MovingPosition *)(parent->unk_08))->unk_06 +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_3E);
    position->unk_0A.as_s16 =
        (s16)(((MovingPosition *)(parent->unk_08))->unk_0A +
              ((Rec_func_800D4BD4_arg1 *)emitter)->unk_40);
    age = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_16 = age;
    if ((s16)age < 0x14) {
        particle_index = 0;
        do {
            particle = allocate_flagged_object_node(0x212);
            if (particle != NULL) {
                initialize_effect_object_state(particle, emitter, position, init_param);
                particle_state = (u8 *)particle + 0x20;
                particle_state->unk_1E = 0xA;
                particle_state->unk_20 = 0xA;
                ((S_800D4DE8_4 *)particle)->unk_10 = D_800D4CB0;
                particle_motion = ((S_800D4DE8_4 *)particle)->unk_08;
                particle_motion->unk_0C =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_10 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_14 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                particle_motion->unk_0A =
                    particle_motion->unk_0A -
                    (entity_height_offsets[((S_800D4DE8_8 *)(((Rec_func_800D4BD4_arg1 *)emitter)->unk_00))->unk_13] >> 1);
            }
            particle_index += 1;
        } while (particle_index < 4);
    }
    life_left = ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E - 1;
    ((Rec_func_800D4BD4_arg1 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_800D4DE8_0_pre *)emitter)[-1].unk_00 = ((S_800D4DE8_0_pre *)emitter)[-1].unk_00 | 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    }
}
