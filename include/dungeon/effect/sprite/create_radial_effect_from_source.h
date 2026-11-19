#ifndef DUNGEON_OVL_18A6800_H
#define DUNGEON_OVL_18A6800_H
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "sdk/libgpu.h"
#include "dungeon/effect/sprite.h"
#include "shared/gpu_packets.h"
#include "sdk/libgpu_types.h"

/* Both positions occupy the node's six 16.16 words. The second triple
 * holds an endpoint when drawing a line and a displacement in the mesh. */
typedef struct LineEndpoints {
    Fixed1616 start[3];
    Fixed1616 end[3];
} LineEndpoints;

/* Eight-byte point copied into the two glow rows and projected from scratch. */
typedef struct GlowPoint {
    u16 x, y, z, pad;
} GlowPoint;

typedef struct Scratch {
    GlowPoint point;
    u8 pad08[0x10];
    void *current;
    u8 pad1c[4];
    u32 *table;
    u8 pad24[0x4c];
    u32 value70;
    u16 half74;
    u8 pad76[2];
    u32 value78;
    u16 half7c;
    u8 pad7e[2];
    u32 value80;
    u16 half84;
    u8 pad86[2];
    u32 value88;
    u16 half8c;
    u8 pad8e[2];
    u32 out90;
    u32 out94;
    u8 pad98[0x28];
    s32 index;
} Scratch;

struct Actor; struct Motion;
/* The effect's colour record: three bytes fading toward black. */
typedef struct EffectColor {
    u8 pad_00[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;
ObjectNodeHeader *create_mesh_fade_effect(ObjectPosition *, SpriteFrameState *);
void update_falling_fading_sprite(struct Actor *, ObjectPosition *, SpriteFrameState *);
void *create_offset_particle_emitter(ObjectPosition *, s16, s16, s16, ObjectNodeHeader *);
void update_offset_particle_emitter(struct GradientLineParticleBody *, ObjectPosition *, SpriteFrameState *);
struct RadialQuadWork;
void update_rotating_quad_effect(struct RadialQuadWork *, ObjectPosition *, SpriteFrameState *);
struct S_80025E4C_1;
s32 queue_linked_shaded_quads(struct S_80025E4C_1 *);
extern u16 D_80026324[];
extern u16 D_80026326;
extern s16 D_80026328[];
extern s16 D_8002632A;
extern u8 radial_effect_colors[];
extern u8 D_80026474[];
extern u8 staged_glow_data[];

struct RadialColorEffectBody;
void create_radial_effect_from_source(struct RadialColorEffectBody *, ObjectPosition *);
s32 queue_glow_grid_quads(void);


#endif
