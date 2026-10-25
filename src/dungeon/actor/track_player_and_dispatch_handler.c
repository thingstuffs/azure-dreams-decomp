#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "engine/script.h"


typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);


typedef struct S_7FFFE25C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_7FFFE25C_1;   /* arg1 in track_player_and_dispatch_handler */


typedef struct S_7FFFE25C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_7FFFE25C_3;   /* ((S_7FFFE25C_1 *)arg1)->unk_0C in track_player_and_dispatch_handler */

typedef struct S_7FFFE25C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    void * unk_14;
} S_7FFFE25C_4;   /* ((Rec_D_80082D58 *)arg0)->unk_58 in track_player_and_dispatch_handler */


extern TownState scene_object_payload_alias;
extern s32 D_800D0420[];

extern s32 scene_idle_callback_address;
extern s32 D_80092698;
extern s32 tracked_actor_callback_address;
extern s32 town_actor_interaction_address;
extern s32 town_input_object_address;
extern s32 town_threshold_interaction_address;
extern s32 town_radial_motion_address;
extern s32 town_busy_countdown_address;
extern s32 town_interaction_action_address;
extern s32 town_threshold_update_address;
extern s32 town_timed_state_address;
extern s32 scene_deferred_dispatch_address;
extern s32 scene_fallback_request_address;
extern s32 town_input_motion_address;

extern void get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void call_the_same_context_both_processing_routines(void *, void *);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);
extern s32 check_object_type_and_data_tag(void *);
extern void unlink_and_remove_scene_object(void *, void *, void *, s32);
extern void retry_sound_sequence_when_ready(void);

/* Adjusts the position and dispatches the current state handler for the owner. */
void track_player_and_dispatch_handler(void *context, S_7FFFE25C_1 *owner, EntityRec *adjusted_pos, s32 dispatch_param)
{
    TownState *state = &scene_object_payload_alias;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current;
    s32 target_z;
    s32 dispatched;

    adjusted_pos->x.v = view_reference_entity.x.v;
    adjusted_pos->y.v = view_reference_entity.y.v;
    adjusted_pos->z.v = view_reference_entity.z.v + offset[2];

    get_smaller_query_result_capped_hex_80_writes_associated_output(adjusted_pos, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(owner, adjusted_pos);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(owner, adjusted_pos);

    target_z = view_reference_entity.z.v + offset[2];
    if (target_z - adjusted_pos->z.v >= 0x10) {
        adjusted_pos->z.v =
            target_z + ((S_7FFFE25C_3 *)(owner->unk_0C))->unk_14;
    }

    current = scene_object_payload_alias.current;
    dispatched = 1;

    {
        void *dispatch_context;
        void *dispatch_owner;
        void *dispatch_pos;
        void *handler;

        if (current == (s32)&town_interaction_action_address || current == (s32)&town_threshold_update_address) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_08;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&town_input_motion_address) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_14;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&town_timed_state_address) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_0C;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&scene_fallback_request_address) {
            unlink_and_remove_scene_object(context, owner, adjusted_pos, dispatch_param);
        } else if (!(current == (s32)&D_80092698 || current == (s32)&tracked_actor_callback_address ||
            current == (s32)&town_actor_interaction_address || current == (s32)&town_busy_countdown_address ||
            current == (s32)&town_input_object_address || current == (s32)&town_threshold_interaction_address ||
            current == (s32)&town_radial_motion_address || current == (s32)&scene_deferred_dispatch_address ||
            current == (s32)&scene_idle_callback_address || service_script_controller() != 0) || previous_owner != (s32)owner) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_10;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else {
            dispatched = 0;
        }
    }
    if (dispatched != 0 && check_object_type_and_data_tag((u8 *)context + 0x4C) != 0) {
        retry_sound_sequence_when_ready();
    }
}
