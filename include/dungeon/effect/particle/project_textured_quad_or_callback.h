#ifndef DUNGEON_OVL_1894800_H
#define DUNGEON_OVL_1894800_H

struct ObjectPosition;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/spell_effect.h"
#include "modules/dungeon_native_abi.h"
typedef struct LinkedRenderNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedRenderNode;

/* Target travel, particle emission, and timed color state for the spell callback. */
typedef struct TargetTravelEffectBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x68];
    union { u16 u; s16 s; } unk_74;
    union { u16 u; s16 s; } unk_76;
    union { u16 u; s16 s; } unk_78;
    u8 unk_7A;
    u8 pad_7B[0x1];
    union { s16 s; u16 u; } unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    u8 pad_82[0x2];
    union { u16 u; s16 s; } unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    u8 pad_8A[0x12];
    u16 unk_9C;
    u8 pad_9E[0x2];
    s16 unk_A0;
    u8 pad_A2[0x8];
    u8 unk_AA;
    u8 pad_AB[0x3];
    u8 unk_AE;
    u8 unk_AF;
} TargetTravelEffectBody;
void project_textured_quad_or_callback(void *,struct ObjectPosition *, SpriteFrameState *, s16);
void draw_textured_sphere_mesh(void *, void *, void *, u16);
s32 project_linked_quad_record(void *, ObjectPosition *, SpriteFrameState *);
s32 draw_chained_object_records(void *, void *, void *);
s32 project_colored_point(u8 *, u8 *);
void advance_point_effect_toward_terrain(void *, s16 *);
void update_effect_quad_and_completion(void *, ObjectPosition *, SpriteFrameState *);
void spawn_randomized_spark_burst(u8 *, void *, u8 *);
void apply_random_duration_actor_status(void *, s32, void *);
/* Signed two-byte view of the first counter; indexed reads use its address. */
extern s16 sphere_particle_effect_updated;
#endif
