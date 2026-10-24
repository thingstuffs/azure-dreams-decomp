#ifndef TOWN_PERSON_H
#define TOWN_PERSON_H

#include "common.h"
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
    u8 pad_74[0xC];
    PersonDescriptor *descriptor;
    u8 pad_84[4];
    s16 target_x;
    s16 target_y;
} PersonObject;

/* The callback's third context has a halfword at +0x12; its other fields
 * are not established by the recovered initializer. */
typedef struct PersonOutput {
    u8 pad_00[0x12];
    s16 unk_12;
} PersonOutput;

/* Install the generic person handlers, store the four per-person data tables
 * (+0x58, +0x5C, +0x7C and the descriptor at +0x80) and register the object in
 * object_index_slots[slot].  The definition still spells the tables as words. */
void initialize_object_and_register_slot(PersonObject *object, s32 slot, void *data_58, void *data_5C,
                                         void *data_7C, void *descriptor);
/* Point descriptor list 1 and the +0x7C table at fixed data; callers pass the
 * whole callback context. */
void initialize_object_referenced_data_pointers(PersonObject *object, s32 context, s8 *output);
s32 get_clamped_transform_coordinate(ObjectPosition *position);

/* Handlers the person callbacks install in PersonObject.handler. */
void advance_actor_reaction_downward(void *context, void *accumulators, void *flag_state);
void tick_countdown_toward_target(void *state, void *current, void *context);
void decrement_object_timer_and_update(void *object, s32 callback_arg_1, s32 callback_arg_2);

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

void reset_person_descriptor_entries(PersonObject *object, s32 unused, s8 *output);
void init_person_slot_four(PersonObject *object);
void apply_person_descriptor_tail(PersonObject *object, ObjectPosition *position, s8 *output);
void reset_person_heading_c00(PersonObject *object, s32 unused, s8 *output);
void step_person_y_up(PersonObject *object, ObjectPosition *position, s8 *output);
void step_person_y_down(PersonObject *object, ObjectPosition *position, s8 *output);
void init_person_timer_sixteen(PersonObject *object, s32 unused, s8 *output);
void init_person_heading_quarter_turn(PersonObject *object, s32 unused, s8 *output);
void init_person_slot_sixty_one(PersonObject *object, s32 unused, PersonOutput *output);

void start_person_target_move(PersonObject *object, ObjectPosition *position, s8 *output);

void install_update_after_flag_clear(PersonObject *object, ObjectPosition *position, s8 *output);

void init_person_slot_thirty_five(PersonObject *object);

void init_person_slot_nineteen(PersonObject *object);

void init_person_slot_thirty_three(PersonObject *object);

void init_person_slot_fifty_one(PersonObject *object);

void init_person_slot_fifty(PersonObject *object);

void init_person_slot_eight(PersonObject *object, s32 context, s8 *output);

#endif
