#ifndef TOWN_PERSON_MOTHER_EVENT_MOTION_G00670_H
#define TOWN_PERSON_MOTHER_EVENT_MOTION_G00670_H
/* G00670: shared declarations for mother event motion. */
/* Original-file evidence (G00670): inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@4A4DC, CL:town/func_800CA30C, CL:town/func_800CA364, CL:town/func_800CA490, PD:town/engine:80113220. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "m2c_compat.h"
#include "town/person/object/initialize_object_entries_api.h"

typedef struct S_800C7AC4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7AC4_1;

typedef struct {
    s32 value;
} Timer;

extern s32 *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(void *object, void *ptr);
extern void install_stored_value_handler(void *object, void *position, s32 update_arg);
extern void func_800C7C3C(void *object, void *position, s32 update_arg);
extern void clear_mother_event_record_field(void *object, void *position, s32 update_arg);
extern u8 town_actor_control[];
extern s32 select_object_setup_path(s32, s32, s32, s32);
extern s32 scale_random_to_unsigned_halfword_limit(s32);
extern u8 D_800C7604[];
extern u8 D_800D5FC4[];
extern s32 D_800C7674;
extern s32 D_800D5FE8;
extern void D_800C78A8();

extern Timer D_80113220;

/* Functions defined in this translation unit. */
void apply_mother_event_motion_offset(void *object, void *position, s32 update_arg);
void reset_mother_event_callback_on_expiry(s32 object, s32 motion, s32 init_data, s32 check_arg);
void initialize_mother_event_actor(void *actor, void *state, s32 init_param);
void choose_mother_event_direction(Rec_func_80094268_arg0 *entity, void *bounds_arg, s32 context_arg);
void initialize_mother_event_with_timer_16(void *object, s32 unused, s32 init_data);

#endif
