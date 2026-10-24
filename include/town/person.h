#ifndef TOWN_PERSON_H
#define TOWN_PERSON_H

#include "common.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "shared/entity.h"


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
