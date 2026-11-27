#ifndef DUNGEON_OVL_19CC800_H
#define DUNGEON_OVL_19CC800_H
#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_native_abi.h"
#include "shared/animation_views.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800249DC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/travel/linked_warp_projectile.h"
#include "dungeon/effect/screen/transform_shade_and_queue_model_quads.h"
#include "sdk/rand.h"
typedef struct FollowerRecord {
    u8 pad_00[8];
    ObjectNodeHeader *owner;
    u8 pad_0C[42];
    s16 angle;
} FollowerRecord;
typedef struct EffectSprite {
    u8 pad_00[6]; s16 unk_06; void *unk_08;
    union { s32 color; s32 unk_0C; } shade;
    u8 pad_10[10]; s16 angle; s16 size; s16 size_max;
} EffectSprite;
extern u16 warp_effect_counters[8];
extern s16 warp_trail_spawn_counter;
extern u8 warp_sprite_entries[12];
extern s32 warp_position_phase;
extern u8 warp_attack_option;
/* Each warp piece supplies its animation table at +0x0C of the 16-byte sprite source. */
typedef struct WarpPieceSlot {
    ShadedModel model;
    AnimEntry *entries;
} WarpPieceSlot;
extern WarpPieceSlot warp_piece_slots[];

struct EffectColor;
struct EventState;
struct Motion;
struct Position;
struct RenderData;

/* Node +0x10 member: body, separate motion tail, separate render record. */
typedef void (*follower_position_update_fn)(FollowerRecord *, ObjectPosition *, struct RenderData *);

void run_warp_effect_sequence(struct EventState *event);
struct WarpPhaseEffectBody;
void advance_effect_phases(struct WarpPhaseEffectBody *object, ObjectPosition *record, SpriteFrameState *sprite);
void *create_warp_phase_effect(EntityRec *source_pos, s32 offset_base);
void run_warp_cutscene(struct Motion *motion, struct Position *position, u8 *color);
void *spawn_nine_warp_trail_sprites(ObjectPosition *src);
void advance_effect_motion_and_speed(MotionRecord *motion, ObjectPosition *position);
void update_effect_position_and_color(ObjectNodeHeader *source, s16 effect_param, s32 render_param);
void copy_follower_owner_position_and_color(FollowerRecord *record, ObjectPosition *position, SpriteFrameState *render);
void create_warp_follower_sprite(ObjectNodeHeader *owner, s16 angle);
void update_warp_camera_and_effects(LinkedWarpProjectileBody *entity, ObjectPosition *motion, SpriteFrameState *sprite);
void *create_linked_sprite_pieces(s16 x, s16 y, s16 z, s16 heading);
void copy_anim_entry_and_widen_fields(AnimFrame *dst, AnimEntry *src);
void advance_animation_index_within_bounds(SpriteFrameState *sprite, s16 *index_step, s32 min_index, s32 max_index);
void set_animation_entry_address(SpriteFrameState *sprite, s16 entry_index);
void set_effect_gte_matrix(AnimFrame *base_matrix, ObjectPosition *position, SpriteFrameState *rotation);
void fade_warp_color_by_half(void *owner, ObjectPosition *unused, SpriteFrameState *sprite);
s32 draw_warp_pieces(AnimFrame *frame, ObjectPosition *position, SpriteFrameState *sprite);
void *create_fading_copy_effect(AnimFrame *source_frame, ObjectPosition *source_position, SpriteFrameState *source_state);
struct Rec_func_80025D28_arg0;
struct SpriteFrameState;
void animate_waving_point_pair_and_fade(struct Rec_func_80025D28_arg0 *state, ObjectPosition *points, struct SpriteFrameState *appearance);
void *create_positioned_linked_mesh_effect(s16 x, s16 y, s16 z, s16 effect_param);
void fade_warp_color_by_quarter(void *record, ObjectPosition *unused, SpriteFrameState *color);
void *spawn_warp_trail_sprites(s16 x, s16 y, s16 z, s16 angle, s16 spawn_actor);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
s32 draw_linked_model_chain(void *, s32, void *);
#endif
