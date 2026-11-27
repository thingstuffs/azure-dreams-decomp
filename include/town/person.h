#ifndef TOWN_PERSON_H
#define TOWN_PERSON_H

struct GameWork;
struct EntityRec;

#include "common.h"
#include "town/system/object_hooks.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "town/person/object/initialize_object_entries_api.h"

void install_person_global_state_handler(TownObjectRecord *object);

struct ReactionAccumulators;
struct ReactionFlagState;

typedef struct EffectScaleState {
    u8 pad_00[0x8];
    s16 scale_enabled;
} EffectScaleState;


/* Root person countdown callback. */
void apply_setup_on_timeout_variant_1(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* choose_reaction_action_and_heading.c */
void choose_reaction_action_and_heading(TownObjectRecord *actor, ObjectPosition *motion, SpriteFrameState *context);

void advance_mother_event_values(TownObjectRecord *state, ObjectPosition *values, SpriteFrameState *setup_context);
void spawn_effect_after_timeout(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *state_context);

/* Effect body allocated by create_bouncing_effect_object: callback at +0x50
 * and signed/unsigned contact counter at +0x90. */
typedef struct OwnerCallbackObject {
    /* 0x00 */ u8 pad_00[0x50];
    /* 0x50 */ void (*callback)(struct OwnerCallbackObject *, ObjectPosition *, SpriteFrameState *);
    /* 0x54 */ u8 pad_54[0x3C];
    /* 0x90 */ union { s16 as_s16; u16 as_u16; } contacts_left;
} OwnerCallbackObject;

/* The callback's third context has a halfword at +0x12; its other fields
 * are not established by the recovered initializer. */
typedef struct PersonOutput {
    u8 pad_00[0x12];
    s16 unk_12;
} PersonOutput;

/* Install the generic person handlers, store the four per-person data tables
 * (+0x58, +0x5C, +0x7C and the descriptor at +0x80) and register the object in
 * object_index_slots[slot]. */
void register_object_slot_with_tables(TownObjectRecord *object, s32 slot, void *data_58, void *data_5C,
                                         void *data_7C, void *descriptor);
/* Point descriptor list 1 and the +0x7C table at fixed data; callers pass the
 * whole callback context. */
struct SpriteFrameState;
void initialize_object_referenced_data_pointers(TownObjectRecord *object, ObjectPosition *context, struct SpriteFrameState *output);
s32 get_clamped_transform_coordinate(ObjectPosition *position);

/* Handlers the person callbacks install in TownObjectRecord.handler. */
void advance_weedy_reaction(TownObjectRecord *context, ObjectPosition *accumulators, SpriteFrameState *flagState);
void tick_countdown_toward_target(TownObjectRecord *state, ObjectPosition *current, SpriteFrameState *sprite);
void call_owner_callback(OwnerCallbackObject *owner, ObjectPosition *motion, SpriteFrameState *output);


/* Zero-terminated entry list shared by the quarter-turn and timed-countdown
 * initializers (contents not yet established). */
extern s32 moving_reaction_entries[];

/* Per-person data tables passed to register_object_slot_with_tables, in call
 * order (+0x58, +0x5C, +0x7C, descriptor).  Their record layouts are not yet
 * established, so they keep address names. */
extern u8 D_800D69B8[], D_800D69BC[], D_800D6988[], D_800D6990[];
extern u8 D_800D71F4[], D_800D71F8[], D_800D71C4[], D_800D71CC[];
extern u8 bunny_state_handlers[], bunny_script_action_handlers[], bunny_animation_lists[], bunny_descriptor[];
extern u8 D_800D60C0[], D_800D60C4[], D_800D6090[], D_800D6098[];
extern u8 barten_state_handlers[], barten_script_action_handlers[], barten_animation_lists[], barten_descriptor[];
extern u8 D_800D6718[], D_800D671C[], D_800D66E8[], D_800D66F0[];
extern u8 D_800D57A4[], D_800D57A8[], D_800D5774[], D_800D577C[];
extern u8 D_800D6C7C[], D_800D6C80[], D_800D6C4C[], D_800D6C54[];

void reset_person_descriptor_entries(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *output);
void init_person_target_move(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void reset_person_heading_three_quarter_turn(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *output);
void step_person_y_up(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void step_person_y_down(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void step_person_x_up(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void step_person_x_down(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);
void start_countdown_toward_target(TownObjectRecord *object, s32 unused, SpriteFrameState *output);
void init_person_heading_quarter_turn(TownObjectRecord *object, s32 unused, SpriteFrameState *output);

void start_person_target_move(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);

void install_update_after_flag_clear(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output);







void init_mia_person(TownObjectRecord *object, ObjectPosition *position_unused, struct SpriteFrameState *sprite_unused);
void *create_owner_following_sprite(TownObjectRecord *linked_object);

void clear_record_indexed_flag(TownObjectRecord *state, ObjectPosition *unused_position, SpriteFrameState *unused_sprite);

/* Access view of event initialization callbacks at +0x4C/+0x50/+0x6C. */
typedef struct PersonSetupState {
    u8 pad_00[0x4C];
    s8 mode;
    s8 phase;
    u8 pad_4E[2];
    void *callback;
    u8 pad_54[0x18];
    s16 timer;
} PersonSetupState;

void begin_mother_event_pause(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *context);
void start_reaction_countdown(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB030_arg0.h"
s32 advance_person_sine_offset(TownObjectRecord *record);
void allocate_variant_object(s32 variant, s32 x, s32 y);
s32 check_heading_past_half_sector(s32 angle, s16 divisions);
void initialize_actor_primary_handler(TownObjectRecord *actor, ObjectPosition *position, SpriteFrameState *sprite);
s32 get_map_cell_step_size(ObjectPosition *coordinates);
void load_position_history_entry(Fixed1616 *destination, s32 entry_index);
s32 map_angle_to_cardinal_direction(s16 angle);
s32 quantize_heading_to_sector(s32 referenceAngle, s16 sectorCount);
void push_position_history(void);

struct S_800AAE30_1;
void fill_position_history(void);
void initialize_mother_event_defaults(TownObjectRecord *object);
void set_person_velocity_from_angle(struct S_800AAE30_1 *object, void *unusedContext, MotionDeltaView *outputVector);

void anyone_now_pos_get(s32 actor_id);

s32 check_town_target_and_callback(const void *object);

#include "records/Rec_D_80082D58.h"
void *create_and_invoke_render_object(TownObjectRecord *owner, s32 resource_index);
void initialize_mother_event_actor(TownObjectRecord *actor, struct ObjectPosition *state, SpriteFrameState *init_param);
void set_bounce_velocity(OwnerCallbackObject *object, ObjectPosition *position, SpriteFrameState *unused_output);
void move_object_velocity(OwnerCallbackObject *owner, ObjectPosition *position, SpriteFrameState *unused_output);
void step_falling_object(OwnerCallbackObject *entity, ObjectPosition *motion, SpriteFrameState *output);
void set_record_data_pointer(TownObjectRecord *record);

void update_person_coordinates(TownObjectRecord *state, ObjectPosition *coords);

void install_actor_response_tables(TownObjectRecord *actor, ObjectPosition *context, SpriteFrameState *input);
void update_person_effect_fade(void *effect_record, ObjectPosition *motion, SpriteFrameState *primitive);

void clear_mother_event_record_field(TownObjectRecord *record, ObjectPosition *unused_position, SpriteFrameState *unused_update_arg);

/* initialize_reaction_data_timer.c */
void start_reaction_vertical_ease(TownObjectRecord *object);
/* initialize_reaction_data_timer_b.c */
void start_reaction_move_toward_target(TownObjectRecord *object);
void start_reaction_ease_to_target(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, struct GameWork *unused_game);

void apply_setup_on_timeout_variant_2(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);
s32 check_actor_data_references_match(TownObjectRecord *actor);
void choose_random_movement_direction(TownObjectRecord *entity, ObjectPosition *movement, SpriteFrameState *context);

void animate_scale_and_restore(TownObjectRecord *state, ObjectPosition *position, SpriteFrameState *scale);

extern u8 slot_81_first_source_table[];

extern u8 slot_81_second_source_table[];

extern u8 slot_81_first_registration_table[];

extern u8 slot_81_second_registration_table[];

void init_person_slot_81(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

#endif
