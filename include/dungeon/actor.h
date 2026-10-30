#ifndef DUNGEON_ACTOR_H
#define DUNGEON_ACTOR_H
#include "common.h"
#include "shared/object_node.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
struct SpriteFrameState;
void reserve_tw_mon_load(s32 request);

void jyotyu_set_reserve_all(void);
void jyotyu_set_reserve_dngn(void);
void announce_familiar_defeat(void *input_data);
void fade_out_and_remove_actor(void *actor_data, s32 unused, SpriteFrameState *visual, void *current_actor);
void begin_action_33_and_dispatch(void *object, void *unused_1, void *unused_2, void *target);
s32 check_active_object_state_567(void);
s32 check_enabled_neighbor_height(s32 world_x, s32 world_y, s16 world_z, u32 direction, s32 disabled);
s32 check_entity_eligibility(void *entity);
s32 check_row_column_or_diagonal_alignment(MovingTile *source, MovingTile *target);
s32 check_tile_path_clear(void *source, void *target);
s32 choose_best_eligible_entry_for_actor(void *actor_arg, s32 action_arg, MovingTile *origin);
void copy_indexed_entry_data(void *entity);
void *find_eligible_nearby_entry(s32 x, s32 y, void *end, void *owner);
void rotate_actor_movement_queue(MovingTile *position, void *state);
void run_saved_actor_action(void *object, void *unused, void *animation, void *actor);
void spawn_salam_particles(ObjectNodeHeader *source, s16 effect_param, s32 render_param);
void update_actor_facing_animation(void *actor, EntityRec *motion, void *sprite, ActorRecord *status);
extern void update_actor_movement_and_map_flags(void *obj, ObjectPosition *move_mode,struct SpriteFrameState *actor, void *map);

struct S_800AB778_1;
s32 advance_actor_removal(struct S_800AB778_1 *state, void *unused_context, SpriteFrameState *visual, void *actor);
s32 check_actor_floor_trap(SpriteFrameState *actor, ActorRecord *target);
void advance_actor_action_controller(void *controller, void *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void begin_actor_flagged_action(Rec_func_800A9E70_arg0 *entity, void *unused, SpriteFrameState *status, EntityRec *event_state);
void initialize_actor_direction_table(void *object, void *unusedContext, SpriteFrameState *tableTarget, void *headingSource);
void select_position_data_and_update_owner(SpriteFrameState *entity, ActorRecord *search_state);
void update_actor_landing(void *motion_state, ObjectPosition *transform, SpriteFrameState *map_entity, ActorRecord *actor);



void dispatch_actor_actions_and_integrate_gravity(void *object, ObjectPosition *motion, void *entity);
void update_actor_gravity(void *object, ObjectPosition *motion, void *entity);

s32 resolve_monster_move_choice(ActorRecord *initial, ObjectPosition *position, SpriteFrameState *sprite, s32 force_move);


s32 roll_actor_stack_split(void *actor, s32 chance);

/* Callback entry points. */
void apply_pending_actor_updates(void *controller, ObjectPosition *move_state, SpriteFrameState *entity, ActorRecord *actor);
void fade_color_toward_half_and_complete(void *effect, s32 unused, void *color);

/* dungeon/actor/movement_overlap_wait_g00334.c */
s32 try_move_actor_to_valid_position(void *action, void *context, void *position, void *entity);

/* dungeon/actor/apply_clamped_actor_value_delta.c */
void apply_clamped_actor_value_delta(void *entity);

/* dungeon/actor/process_selected_actor_record.c */
s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *record);
s32 check_scaled_value_threshold(ActorRecord *state);


struct S_800C8DB0_0;
s32 attempt_action_six_if_eligible(struct S_800C8DB0_0 *entity, s16 threshold, s8 action_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 select_dungeon_spawn_tile(u8 *x_out, u8 *y_out);

s32 lookup_definition_pair_value(s16 firstKey, s16 secondKey);

struct DungeonSlot;
struct CallbackOwner;
struct ActorHopExtra;
struct ActorHopMotion;
struct ActorHopParams;
struct ActorHopState;
s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
s32 advance_staged_entity_load(s32 unused, u8 *entity);
void advance_status_timers(void *record);
void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
s32 cap_pending_actor_value_delta(void *entry);
s16 check_adjacent_tile_height_clearance(u16 x, u16 y, s32 z, void *skip_check);
s32 check_entity_flag_20000000(u8 *entity);
void *choose_best_eligible_entry(void *owner_arg, void *start, s32 score_limit);
void *create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
s32 find_matching_initial_stat_slot(u8 *record);
s32 find_slot_by_definition_kind(u8 *slots, u8 kind);
s32 find_type_13_slot_index(struct DungeonSlot *targetSlot);
void install_actor_action_handler_after_floor_trap_check(struct CallbackOwner *owner, ObjectPosition *position, void *tile, ActorRecord *actor);
s32 is_linked_entity_flagged_10000000(EntityRec *entity);
s32 is_linked_entity_flagged_2000000(EntityRec *entity);
s32 is_linked_entity_flagged_80000(EntityRec *entity, void *unused_context);
void on_actor_status_updated(void *actor);
s32 resolve_actor_floor_trap_once(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s16 resolve_alternate_spell_id(s32 tile_index);
s32 select_creature_action_and_target(void *unused, u8 *position, ActorRecord *creature, s32 lower_limit, u16 upper_limit, s8 *status_out_addr);
s16 select_highest_value_item(s32 records_addr, s32 item_kind);
s32 update_actor_defeat_removal(ActorRecord *state, ObjectPosition *position, struct SpriteFrameState *sprite, ActorRecord *entity_data);
s32 update_actor_hop_and_grow(struct ActorHopState *state, struct ActorHopMotion *motion, struct ActorHopParams *params, struct ActorHopExtra *extra);
s32 update_thrown_actor_travel(void *move_state, ObjectPosition *motion, SpriteFrameState *tile_pos, ActorRecord *actor);

#include "shared/dungeon_item_entries.h"
struct Actor;
struct Ctx;
s32 choose_usable_ability_or_attack(struct Actor *actor, struct Actor *target, u16 *out_angle, s32 prefer_ability);
s32 feed_actor_restore_mp(ActorRecord *state, s32 mode, DungeonItemEntry *item);
s32 is_linked_entity_flagged_100000(EntityRec *entity);
s32 trigger_actor_floor_trap(struct Actor *actor, struct Ctx *ctx);

#endif
