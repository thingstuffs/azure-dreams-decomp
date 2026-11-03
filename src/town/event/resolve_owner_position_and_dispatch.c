#include "shared/position_query.h"
#include "town/scene/collision.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "engine/script.h"
#include "shared/position_views.h"
#include "town/scene.h"
#include "town/scene/motion.h"
#include "town.h"
#include "town/event.h"
#include "town/event/object.h"
#include "town/map.h"
#include "town/data.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/player/position_handlers.h"
#include "town/player/state.h"


typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);


typedef struct S_8009B9BC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009B9BC_1;   /* arg1 in resolve_owner_position_and_dispatch */


typedef struct S_8009B9BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009B9BC_3;   /* ((S_8009B9BC_1 *)arg1)->unk_0C in resolve_owner_position_and_dispatch */

typedef struct S_8009B9BC_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    void * unk_10;
    s32 unk_14;
} S_8009B9BC_4;   /* ((Rec_D_80082D58 *)arg0)->unk_58 in resolve_owner_position_and_dispatch */


extern TownState scene_object_payload_alias;
extern s32 D_800D0420[];













extern s32 town_input_motion_address;

extern void unlink_and_remove_scene_object(void *, void *, void *, s32); /* Unprototyped: retail call passes more arguments than the callee reads */

/* Resolve the owner position and dispatch its handler for the current town state. */
void resolve_owner_position_and_dispatch(void *object, S_8009B9BC_1 *owner, EntityRec *resolved_pos, s32 dispatch_param)
{
    TownState *state = &scene_object_payload_alias;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current_state;
    s32 target_z;
    s32 dispatched;

    resolved_pos->x.v = view_reference_entity.x.v;
    resolved_pos->y.v = view_reference_entity.y.v;
    resolved_pos->z.v = view_reference_entity.z.v + offset[2];

    get_smaller_query_result_capped_hex_80_writes_associated_output(resolved_pos, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(owner, resolved_pos);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(owner, resolved_pos);

    target_z = view_reference_entity.z.v + offset[2];
    if (target_z - resolved_pos->z.v >= 0x10) {
        resolved_pos->z.v =
            target_z + ((S_8009B9BC_3 *)(owner->unk_0C))->unk_14;
    }

    current_state = scene_object_payload_alias.current;
    dispatched = 1;

    if (current_state == (s32)update_actor_interaction_actions || current_state == (s32)update_threshold_object) {
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_08)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)&town_input_motion_address) {
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_14)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)update_entity_and_dispatch_timed_state) {
                /* MATCH: preserve the fourth argument register allocation. */
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_0C)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)dispatch_fallback_request) {
        unlink_and_remove_scene_object(object, owner, resolved_pos, dispatch_param);
    } else {
        if (!(current_state == (s32)update_actor_with_interaction_state || current_state == (s32)update_actor_movement_and_interaction ||
              current_state == (s32)update_actor_position_and_interaction || current_state == (s32)update_threshold_countdown_with_busy_check ||
              current_state == (s32)update_town_object_from_input || current_state == (s32)&town_threshold_interaction_address ||
              current_state == (s32)update_actor_movement_with_radial_effects || current_state == (s32)dispatch_deferred_callback ||
              current_state == (s32)no_op_scene_callback_b || service_script_controller() != 0) ||
            previous_owner != (s32)owner) {
            ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_10)(object, owner, resolved_pos,
                dispatch_param);
        } else {
            dispatched = 0;
        }
    }
    if (dispatched != 0 && check_object_type_and_data_tag((u8 *)object + 0x4C) != 0) {
        retry_sound_sequence_when_ready();
    }
}
