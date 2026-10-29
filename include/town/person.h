#ifndef TOWN_PERSON_H
#define TOWN_PERSON_H

#include "common.h"
#include "town/system/object_hooks.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "shared/entity.h"
#include "town/person/object/initialize_object_entries_api.h"


/* choose_reaction_action_and_heading.c */
void choose_reaction_action_and_heading(Rec_func_800C9B44_arg0 *actor, EntityRec *motion, s32 context);

/* Town script objects use a descriptor and callback at +0x80/+0x54.
 * These are separate from the pooled dungeon ActorRecord. */
typedef struct PersonDescriptor {
    s32 *entries[10];
} PersonDescriptor;

typedef struct PersonObject {
    u8 pad_00[0x54];
    void *handler;
    s32 unk_58;
    s32 unk_5C;
    s32 slot;
    u8 pad_64[8];
    s16 timer;
    u8 pad_6E[4];
    s16 heading;
    u8 pad_74[8];
    s32 **data_7C;
    PersonDescriptor *descriptor;
    u8 pad_84[4];
    s16 target_x;
    s16 target_y;
    u8 pad_8C[0xA];
    u8 variant;
} PersonObject;

/* The callback's third context has a halfword at +0x12; its other fields
 * are not established by the recovered initializer. */
typedef struct PersonOutput {
    u8 pad_00[0x12];
    s16 unk_12;
} PersonOutput;

/* Install the generic person handlers, store the four per-person data tables
 * (+0x58, +0x5C, +0x7C and the descriptor at +0x80) and register the object in
 * object_index_slots[slot]. */
void initialize_object_and_register_slot(PersonObject *object, s32 slot, void *data_58, void *data_5C,
                                         void *data_7C, void *descriptor);
/* Point descriptor list 1 and the +0x7C table at fixed data; callers pass the
 * whole callback context. */
struct SpriteFrameState;
void initialize_object_referenced_data_pointers(PersonObject *object, void *context, struct SpriteFrameState *output);
s32 get_clamped_transform_coordinate(ObjectPosition *position);

/* Handlers the person callbacks install in PersonObject.handler. */
void advance_actor_reaction_downward(void *context, void *accumulators, void *flag_state);
void tick_countdown_toward_target(void *state, void *current, void *context);


/* Zero-terminated entry list shared by the quarter-turn and timed-countdown
 * initializers (contents not yet established). */
extern s32 D_800D72AC[];

/* Per-person data tables passed to initialize_object_and_register_slot, in call
 * order (+0x58, +0x5C, +0x7C, descriptor).  Their record layouts are not yet
 * established, so they keep address names. */
extern u8 D_800D69B8[], D_800D69BC[], D_800D6988[], D_800D6990[];
extern u8 D_800D71F4[], D_800D71F8[], D_800D71C4[], D_800D71CC[];
extern u8 D_800D5270[], D_800D5274[], D_800D5240[], D_800D5248[];
extern u8 D_800D60C0[], D_800D60C4[], D_800D6090[], D_800D6098[];
extern u8 D_800D5478[], D_800D547C[], D_800D5448[], D_800D5450[];
extern u8 D_800D6718[], D_800D671C[], D_800D66E8[], D_800D66F0[];
extern u8 D_800D57A4[], D_800D57A8[], D_800D5774[], D_800D577C[];
extern u8 D_800D6C7C[], D_800D6C80[], D_800D6C4C[], D_800D6C54[];

void reset_person_descriptor_entries(PersonObject *object, s32 unused, SpriteFrameState *output);
void apply_person_descriptor_tail(PersonObject *object, ObjectPosition *position, SpriteFrameState *output);
void reset_person_heading_c00(PersonObject *object, s32 unused, SpriteFrameState *output);
void step_person_y_up(PersonObject *object, ObjectPosition *position, SpriteFrameState *output);
void step_person_y_down(PersonObject *object, ObjectPosition *position, SpriteFrameState *output);
void init_person_timer_sixteen(PersonObject *object, s32 unused, SpriteFrameState *output);
void init_person_heading_quarter_turn(PersonObject *object, s32 unused, SpriteFrameState *output);

void start_person_target_move(PersonObject *object, ObjectPosition *position, SpriteFrameState *output);

void install_update_after_flag_clear(PersonObject *object, ObjectPosition *position, SpriteFrameState *output);







void initialize_object_configuration_x(PersonObject *object);

void clear_record_indexed_flag(void *state, s32 unused_context, void *unused_state_context);

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

void begin_mother_event_pause(PersonSetupState *object, void *unused, void *context);
void initialize_reaction_object_four(PersonSetupState *object, void *unused, void *context);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB030_arg0.h"
s32 advance_person_lookup_value(Rec_func_800AB030_arg0 *record);
void allocate_variant_object(s32 variant, s32 x, s32 y);
s32 check_heading_past_half_sector(s32 angle, s16 divisions);
void func_800CA60C(Rec_func_80094268_arg0 *actor, void *unused, void *output);
s32 get_person_lookup_step(Rec_func_800AAE98_arg0 *coordinates);
void load_record_halfwords_3(void *destination, s32 entry_index);
s32 map_angle_to_cardinal_direction(s16 angle);
s32 quantize_heading_to_sector(s32 referenceAngle, s16 sectorCount);
void shift_history_and_store_current_values(void);

#include "shared/position_views.h"
struct S_800AAE30_1;
struct S_800C7C88_0;
void fill_person_records(void);
void initialize_mother_event_defaults(struct S_800C7C88_0 *object);
void initialize_person_vector(struct S_800AAE30_1 *object, void *unusedContext, MotionDeltaView *outputVector);

void anyone_now_pos_get(s32 actor_id);

#endif
