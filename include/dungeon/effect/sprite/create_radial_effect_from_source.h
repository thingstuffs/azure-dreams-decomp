#ifndef DUNGEON_OVL_18A6800_H
#define DUNGEON_OVL_18A6800_H
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "sdk/libgpu.h"
struct FadeEndpoints; struct FadeSettings;
 struct S_80025160_1;
struct Actor; struct Motion;
/* The effect's colour record: three bytes fading toward black. */
typedef struct EffectColor {
    u8 pad_00[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;
ObjectNodeHeader *create_mesh_fade_effect(struct FadeEndpoints *, struct FadeSettings *);
void *create_object_offset(MovingPosition *, s16, s16, s16, s32);
void emit_offset_particles_then_wait_for_release(void *, s32, struct S_80025160_1 *);
void update_falling_fading_sprite(struct Actor *, struct Motion *, SpriteFrameState *);
struct RadialQuadWork;
void update_rotating_quad_effect(struct RadialQuadWork *, ObjectPosition *, SpriteFrameState *);
s32 queue_linked_shaded_quads(void *);
extern u16 D_80026324[];
extern u16 D_80026326;
extern s16 D_80026328[];
extern s16 D_8002632A;
extern u8 radial_effect_colors[];
extern u8 D_80026474[];
extern u8 staged_glow_data[];

void create_radial_effect_from_source(); /* Slot contract: loading images do not establish one callee contract. */
s32 queue_glow_grid_quads(void);


#endif
