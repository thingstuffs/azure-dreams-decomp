#ifndef DUNGEON_EFFECT_H
#define DUNGEON_EFFECT_H

/* Function contracts owned by src/dungeon/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "dungeon/effect/object.h"
#include "dungeon/effect/motion/variant_effect_with_random_motion.h"

/* Body created for the player tile actor's fading primitive callback. */
typedef struct SourceLinkedFadeEffectBody {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void *unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} SourceLinkedFadeEffectBody;
void apply_effect_bonuses(s16 effect_id, ActorRecord *unused_arg, ActorRecord *record);
void *create_mode_configured_object(s16 mode, s32 part_b_byte_24, s32 part_b_byte_25, s32 part_a_value, s32 part_b_value);
void create_record_with_effect_callback(void);
void *create_actor_value_popup(s32 flags, void *source_data, s16 value, u16 callback_mode);
void advance_actor_hop_and_dispatch(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *render, ActorRecord *context);
void dispatch_target_action(ActorRecord *actor, s32 action_context, SpriteFrameState *destination, ActorRecord *target);
void emit_scattered_effects_unless_blocked(void *source);
void process_nearby_object_midpoint(u8 *start_obj, u8 *end_obj, s16 start_height, s16 end_height, s16 call_param, s32 call_arg);
void run_indexed_callback_list(s16 list_index);
void spawn_directed_and_scattered_particles(s32 x, s32 y, s32 z);
void *spawn_randomized_particle_burst(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound);




void advance_actor_attack_sequence(ActorRecord *action_state, ObjectPosition *motion, void *animation, ActorRecord *actor);
void advance_effect_fade_and_remove(VariantEffectWithRandomMotionBody *effect, ObjectPosition *motion, SpriteFrameState *primitive);

struct PointRecord;
struct ObjectPosition;
s32 draw_ball_effect_points(struct PointRecord *, struct ObjectPosition *);

/* Callback entry points. */
s32 process_linked_states_mode_zero(ActorRecord *initial_state, ObjectPosition *context, SpriteFrameState *data);
void jitter_effect_position_and_fade(void *effect, void *position, void *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_moving_views.h"
void update_oriented_offset_effect_position(PayloadObjectBody *state, MovingPosition *position);

struct Object;
struct Other;
s32 prepare_quarter_damage_return(struct Object *object, ActorRecord *source);
s32 process_linked_mesh_states_mode_0(void *initial_state, s32 value, void *data);
s32 select_nearby_target_and_initialize_slot(void *tracked_object, void *target_data, s32 target_id, s32 slot_value);
void setup_object_within_planar_range(void *object, s32 x, s32 y, s32 height, s32 mode, s32 settings);

struct ObjectNodeHeader;
void *create_effect_or_fallback(u32 x, u32 y, s32 z, void *effect_data);
void *create_moving_fading_particle(ObjectPosition *origin, s16 angle, s16 radius, s16 height_offset, struct ObjectNodeHeader **allocation_head);
void transform_mesh_and_append_draw_packets(u8 *params, ObjectPosition *record, void *mesh_data, s32 depth_offset);

s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);

void add_value_to_active_entries_at_tile(s16 x, s16 y, s32 amount);
void * create_dual_grid_trap_effect(s32 center_x, s32 center_y, s16 unused_value, ActorRecord *unused_data, s32 reverse_offset);
void create_five_part_target_effect(u16 x, u16 y, s16 z);
void *create_owned_tile_center_effect(s16 tile_x, u16 tile_y, s16 height, void *owner);
void *create_tile_center_quad_effect(s16 tile_x, s16 tile_y, s16 z, s16 tail_value, s16 render_mode, u16 tail_config);
void damp_effect_motion_and_fade(void *effect, s32 *motion, SpriteFrameState *primitive);
void dispatch_action_callback_by_opcode(u8 *w);
void draw_sprite_parts_as_quad_grid(ActorRecord *context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias);
void *func_8002522C(ObjectPosition *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader **allocation_head);
void mark_all_actors_with_high_flag(void);
s32 run_action_ten_if_eligible(ActorRecord *entity, s8 action_arg);
void set_value_of_active_entries_at_tile(s16 x, s16 y, s16 value);
void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound);
s32 take_map_item_slot(ActorRecord *object, s16 slot);
void update_target_tracking_and_transition(void *tracker);

struct S_800B45E0_0;
struct S_800B490C_0;
void update_anchored_fading_effect(struct S_800B45E0_0 *effect, ObjectPosition *motion, SpriteFrameState *sprite);
void update_attached_fading_effect(struct S_800B490C_0 *effect, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
