#include "common.h"
#include "dungeon/effect/particle.h"
#include "shared/dungeon_moving_views.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_7FFE89B0_0_pre {
    u16 unk_00;
} S_7FFE89B0_0_pre;   /* the 0x2 bytes before arg0 in emit_parent_relative_particles, addressed as arg0[-1] */

typedef struct S_7FFE89B0_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_7FFE89B0_0;   /* arg0 in emit_parent_relative_particles */


typedef struct S_7FFE89B0_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE89B0_2;

typedef struct S_7FFE89B0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
} S_7FFE89B0_3;

typedef struct S_7FFE89B0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_7FFE89B0_4;



typedef struct S_7FFE89B0_6 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFE89B0_6;   /* ((S_7FFE89B0_0 *)arg0)->unk_00 in emit_parent_relative_particles */



void *func_7003CF18();
s32 func_700750E0();
M2C_UNK func_7010B864();
extern s32 particle_object_flags;
extern u8 emitter_height_offsets[];
extern u16 emitted_effect_counter;
extern M2C_UNK D_8010B4EC;

/* Emit particles at the parent-relative position and retire the emitter when its lifetime expires. */
void emit_parent_relative_particles(void *emitter_arg, ObjectPosition *position, M2C_UNK spawn_context) {
    S_7FFE89B0_0 *emitter = emitter_arg;
    s32 spawn_index;
    u16 age;
    u16 lifetime;
    S_7FFE89B0_2 *parent;
    S_7FFE89B0_4 *particle_state;
    S_7FFE89B0_3 *particle;

    parent = emitter->unk_24;
    position->x.w.i = (s16) (((MovingPosition *)(parent->unk_08))->x
        + emitter->unk_3C);
    position->y.w.i = (s16) (((MovingPosition *)(parent->unk_08))->y
        + emitter->unk_3E);
    position->z.w.i = (s16) (((MovingPosition *)(parent->unk_08))->z
        + emitter->unk_40);
    age = emitter->unk_16 + 1;
    emitter->unk_16 = age;
    if ((s16) age < 0x14) {
        spawn_index = 0;
        do {
            particle = func_7003CF18(0x212);
            spawn_index += 1;
            if (particle != NULL) {
                func_7010B864(particle, emitter, position, spawn_context);
                particle->unk_3E = 0xA;
                particle->unk_40 = 0xA;
                particle->unk_10 = &D_8010B4EC;
                particle_state = particle->unk_08;
                particle_state->unk_0C = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                particle_state->unk_10 = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                particle_state->unk_14 = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                particle_state->unk_0A = (u16) (particle_state->unk_0A
                    - (emitter_height_offsets[((S_7FFE89B0_6 *)(emitter->unk_00))->unk_13] >> 1));
            }
        } while (spawn_index < 4);
    }
    lifetime = emitter->unk_1E - 1;
    emitter->unk_1E = lifetime;
    if ((lifetime << 0x10) <= 0) {
        u16 *active_count = &emitted_effect_counter;
        u16 next_active_count;

        (*(u16 *)((u8 *)emitter + -2)) = (u16) (((S_7FFE89B0_0_pre *)emitter)[-1].unk_00 | 0x8000);
        next_active_count = *active_count - 1;
        particle_object_flags |= 0x8000;
        *active_count = next_active_count;
    }
}
