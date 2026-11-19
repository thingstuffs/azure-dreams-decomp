#ifndef DUNGEON_OVL_1894800_H
#define DUNGEON_OVL_1894800_H

struct ObjectPosition;
#include "common.h"
#include "dungeon/effect/particle/rotating_effect_quad.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_part_command.h"
#include "dungeon/effect/spell_effect.h"
#include "modules/dungeon_native_abi.h"
typedef struct LinkedRenderNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedRenderNode;

/* Payload created with the 0x211 colored point node and read by its draw callback. */
typedef struct TerrainSeekingPointBody {
    u8 pad_00[0x8];
    s32 color;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 intensity;
    s16 divisor;
    u8 pad_36[0x12];
    s32 z_velocity;
} TerrainSeekingPointBody;

/* Target travel, particle emission, and timed color state for the spell callback. */
typedef struct TargetParticleStatusSpellBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x68];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    u8 unk_7A;
    u8 pad_7B[0x1];
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    u8 pad_82[0x2];
    s16 unk_84;
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
} TargetParticleStatusSpellBody;
/* The status spell registers the sphere renderer and spark update on this child. */
typedef struct SphereSpriteSource {
    SpritePartCommand command;
} __attribute__((packed)) SphereSpriteSource;

typedef struct TexturedSparkSphereBody {
    s16 mode;
    s16 timer;
    u8 pad04[6];
    s16 columns;
    s16 rows;
    s16 latitude_span;
    s16 longitude_offset;
    s16 unk_12;
    u8 pad14[6];
    s16 current_radius;
    s16 unk_1C;
    u8 pad1E[0xE];
    SphereSpriteSource sprite_source;
    ActorRecord *owner;
    ActorRecord *target;
    TargetParticleStatusSpellBody *spell;
    u8 pad44[0x24];
    Fixed1616 radius;
    u8 pad6C[8];
    s32 velocity;
    u8 pad78[8];
    s32 acceleration;
} TexturedSparkSphereBody;
void project_textured_quad_or_callback(void *,struct ObjectPosition *, SpriteFrameState *, s16);
void draw_textured_sphere_mesh(TexturedSparkSphereBody *, ObjectPosition *, SpriteFrameState *, u16);
s32 project_linked_quad_record(void *, ObjectPosition *, SpriteFrameState *);
s32 draw_chained_object_records(TexturedSparkSphereBody *, ObjectPosition *, SpriteFrameState *);
s32 project_colored_point(TerrainSeekingPointBody *, ObjectPosition *);
void advance_point_effect_toward_terrain(TerrainSeekingPointBody *, ObjectPosition *);
void update_effect_quad_and_completion(RotatingEffectQuadBody *, ObjectPosition *, SpriteFrameState *);
void spawn_randomized_spark_burst(TexturedSparkSphereBody *, ObjectPosition *, SpriteFrameState *);
void apply_water_protect_status(void *, s32, void *);
/* Signed two-byte view of the first counter; indexed reads use its address. */
extern s16 sphere_particle_effect_updated;
extern const u8 no_effect_target_prefix[48];
extern const u8 no_effect_target_period[4];
#endif
