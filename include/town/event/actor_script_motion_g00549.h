#ifndef TOWN_EVENT_ACTOR_SCRIPT_MOTION_G00549_H
#define TOWN_EVENT_ACTOR_SCRIPT_MOTION_G00549_H
/* inferred-strong G00549: actor_script_motion_g00549; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009DB64. */

#include "common.h"
#include "town/scene/collision.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/position_query.h"

typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[4];
    s32 index;
    void *owner;
    u8 pad_20[0x1A];
    u8 state;
    u8 state_3B;
} TownControl;

typedef struct {
    void (*func0)(void);
    void *pad_04[5];
    void (*func18)(void);
} TownVtable;

typedef struct {
    u8 pad_00[0x58];
    TownVtable *vtable;
} TownObject;

typedef struct S_8009B2C4_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009B2C4_0;

/* (u8 *)arg1 + D_800CFDD8[index] in dispatch_active_town_object_script */
typedef struct S_8009B2C4_1 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009B2C4_1;

extern void initialize_target_motion_state(TownObject *object, void *owner, void *context, void *extra_ptr);
extern void initialize_target_motion(TownObject *object, void *owner, void *context, void *extra_ptr);
extern s32 scene_object_payload_alias;
extern u8 D_80091F64[];
extern u8 D_8009204C[];
extern u8 D_800920F4[];
extern u8 D_800924EC[];
extern u8 D_80092698[];
extern u8 tracked_actor_callback_address[];
extern s32 D_800CFCCC;
extern s32 D_800CFDD8[];
extern s16 get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void set_the_state_flag_initialize_s_fixed_point_clear_paired_field(void *, void *, s16);
extern void call_the_same_context_both_processing_routines(void *, void *);
extern void set_actor_drop_state(void *, void *, void *, void *);
extern u8 actor_surface_callback_address[];
extern u8 actor_output_update_address[];
extern u8 actor_moving_target_address[];
extern void set_actor_motion_state(void *, void *, void *, void *);

extern TownControl town_actor_control;

/* Functions defined in this translation unit. */
s32 dispatch_active_town_object_script(TownObject *object, void *owner, void *context, void *extra_ptr);
void update_actor_surface_motion(void *actor, void *subject, void *motion, void *context);
void update_actor_slots_and_output(void *state_owner, void *update_target, void *update_context, void *output);

#endif
