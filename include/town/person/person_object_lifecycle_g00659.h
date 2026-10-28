#ifndef TOWN_PERSON_PERSON_OBJECT_LIFECYCLE_G00659_H
#define TOWN_PERSON_PERSON_OBJECT_LIFECYCLE_G00659_H
/* Person object lifecycle (G00659). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C5ABC, CL:town/func_800C6064, PD:town/engine:800D5028. */

#include "common.h"
#include "town/scene/list_setup.h"
#include "records/Rec_func_80094268_arg0.h"
/* extern */
#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */
#include "m2c_compat.h"
#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "shared/slus_callbacks.h"
/* extern */
#include "town/system/clear_object_status_and_dispatch_target_api.h" /* extern */

/* extern */
typedef struct S_800C3960_0 S_800C3960_0;

typedef struct {
    u8 pad0[0x0C];
    s32 *field0c;
    u8 pad10[0x40];
    void (*callback)(void *, void *, void *);
    u8 pad54[0x10];
    s16 field64;
    u8 pad66[0x0A];
    u8 state70;
    u8 flags71;
    s16 field72;
    s16 field74;
    u8 pad76[2];
    s32 **table78;
} TargetObj;

typedef void (*FuncPtr)(void *, void *, void *);

/* extern */
struct Rec_func_8008F074_arg0;

void unlink_node_if_registered(void *block_data);
s32 classify_object_against_bounds(Rec_func_80094268_arg0 *, void *);
/* extern */
void clear_object_slot_and_mark_removed(void *);
void call_object_callback(S_800C3960_0 *object, void *context, void *motion);

s32 quantize_heading_to_sector(s32, s16);
s32 check_heading_past_half_sector(s32, s16);
extern M2C_UNK D_800D5028;
extern M2C_UNK D_800D5040;
extern M2C_UNK D_800D5058;
extern s32 runtime_is_record_field_set(void *);
#include "town/person/state_updates.h"
void register_node_if_unregistered(void *block_data, void *registration_id);

/* Functions defined in this translation unit. */
void update_object_position_or_cleanup(Rec_func_80094268_arg0 *object, void *position, void *motion);
void update_object_motion_and_flags(TargetObj *obj, void *callback_arg, void *motion_data);
void dispatch_object_state(void *object, void *context, void *dispatch_data);
void initialize_person_object(Rec_func_80094268_arg0 *object, void *context, void *animation);

#endif
