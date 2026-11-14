#ifndef DUNGEON_OVL_189A800_H
#define DUNGEON_OVL_189A800_H
struct ObjectPosition;
struct RandomRadialVectorEffectBody;


struct SpriteFrameState;
struct ObjectPosition;
#include "modules/dungeon_native_abi.h"
#include "shared/position_views.h"

/* Record views shared by the mesh renderer and linked-record walker. */



typedef struct S_func_800241A8_4 {
    u8 pad_00[0x4E];
    u8 unk_4E;
    u8 pad_4F[0x9];
    union {
        s16 as_s16_58;
        u16 as_u16_58;
    } unk_58;
    union {
        s16 as_s16_5A;
        u16 as_u16_5A;
    } unk_5A;
    union {
        s16 as_s16_5C;
        u16 as_u16_5C;
    } unk_5C;
    union {
        s16 as_s16_5E;
        u16 as_u16_5E;
    } unk_5E;
    union {
        s16 as_s16_60;
        u16 as_u16_60;
    } unk_60;
    union {
        s16 as_s16_62;
        u16 as_u16_62;
    } unk_62;
    union {
        s16 as_s16_64;
        u16 as_u16_64;
    } unk_64;
    union {
        s16 as_s16_66;
        u16 as_u16_66;
    } unk_66;
    union {
        s16 as_s16_68;
        u16 as_u16_68;
    } unk_68;
    union {
        s16 as_s16_6A;
        u16 as_u16_6A;
    } unk_6A;
    union {
        s16 as_s16_6C;
        u16 as_u16_6C;
    } unk_6C;
    union {
        s16 as_s16_6E;
        u16 as_u16_6E;
    } unk_6E;
} S_func_800241A8_4;

void transform_and_queue_mesh_primitives(S_func_800241A8_4 *,struct ObjectPosition *,struct SpriteFrameState *, s32);
/* Bank callbacks whose definitions precede their users in the native TU. */
void rotate_point_cloud_until_expired(struct RandomRadialVectorEffectBody *object, struct ObjectPosition *unused, SpriteFrameState *target);
struct StarEdgeEffectBody;
void advance_fading_effect_animation(struct StarEdgeEffectBody *effect_data, struct ObjectPosition *unused_arg, SpriteFrameState *color_data);
struct S_8187BE9C_1;
struct ProjectileTrailFlashBody;
void update_projectile_trail_flash(struct ProjectileTrailFlashBody *effect, s32 unused, SpriteFrameState *primitive);
s32 draw_chained_mesh_records(void *record, void *context, void *data);
struct RandomRadialVectorEffectBody;
struct SignedPositionView;
s32 project_shaded_points_to_ordering_table(struct RandomRadialVectorEffectBody *points, ObjectPosition *position, u8 *orientation);
struct StarSequenceBody;
void initialize_star_effect_sequence(struct StarSequenceBody *state_data, void *source_data);
#endif
