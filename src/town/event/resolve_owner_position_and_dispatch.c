#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"


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

extern s32 D_80090A6C;
extern s32 D_80092698;
extern s32 D_800927EC;
extern s32 D_80092A84;
extern s32 D_80092CD4;
extern s32 D_80092DA8;
extern s32 D_80092ECC;
extern s32 D_80092FF0;
extern s32 D_800930E4;
extern s32 D_80093250;
extern s32 D_80093328;
extern s32 D_800933FC;
extern s32 D_80093638;
extern s32 D_800AA5F8;

extern void get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void call_the_same_context_both_processing_routines(void *, void *);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);
extern s32 service_script_controller();
extern s32 check_object_type_and_data_tag(void *);
extern void func_8009C340(void *, void *, void *, s32);
extern void retry_sound_sequence_when_ready(void);

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

    if (current_state == (s32)&D_800930E4 || current_state == (s32)&D_80093250) {
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_08)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)&D_800AA5F8) {
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_14)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)&D_80093328) {
                /* MATCH: preserve the fourth argument register allocation. */
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)object)->unk_58))->unk_0C)(object, owner, resolved_pos,
            dispatch_param);
    } else if (current_state == (s32)&D_80093638) {
        func_8009C340(object, owner, resolved_pos, dispatch_param);
    } else {
        if (!(current_state == (s32)&D_80092698 || current_state == (s32)&D_800927EC ||
              current_state == (s32)&D_80092A84 || current_state == (s32)&D_80092FF0 ||
              current_state == (s32)&D_80092CD4 || current_state == (s32)&D_80092DA8 ||
              current_state == (s32)&D_80092ECC || current_state == (s32)&D_800933FC ||
              current_state == (s32)&D_80090A6C || service_script_controller() != 0) ||
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
