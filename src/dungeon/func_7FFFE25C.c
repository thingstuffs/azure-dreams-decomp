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


typedef struct S_7FFFE25C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_7FFFE25C_1;   /* arg1 in func_7FFFE25C */


typedef struct S_7FFFE25C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_7FFFE25C_3;   /* ((S_7FFFE25C_1 *)arg1)->unk_0C in func_7FFFE25C */

typedef struct S_7FFFE25C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    void * unk_14;
} S_7FFFE25C_4;   /* ((Rec_D_80082D58 *)arg0)->unk_58 in func_7FFFE25C */


extern TownState D_800834B8;
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
extern s32 func_800352FC();
extern s32 check_object_type_and_data_tag(void *);
extern void func_8009C340(void *, void *, void *, s32);
extern void retry_sound_sequence_when_ready(void);

/* Adjusts the position and dispatches the current state handler for the owner. */
void func_7FFFE25C(void *context, S_7FFFE25C_1 *owner, EntityRec *adjusted_pos, s32 dispatch_param)
{
    TownState *state = &D_800834B8;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current;
    s32 target_z;
    s32 dispatched;

    adjusted_pos->x.v = D_80083780.x.v;
    adjusted_pos->y.v = D_80083780.y.v;
    adjusted_pos->z.v = D_80083780.z.v + offset[2];

    get_smaller_query_result_capped_hex_80_writes_associated_output(adjusted_pos, ((u8 *)&D_800FE488));
    call_the_same_context_both_processing_routines(owner, adjusted_pos);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(owner, adjusted_pos);

    target_z = D_80083780.z.v + offset[2];
    if (target_z - adjusted_pos->z.v >= 0x10) {
        adjusted_pos->z.v =
            target_z + ((S_7FFFE25C_3 *)(owner->unk_0C))->unk_14;
    }

    current = D_800834B8.current;
    dispatched = 1;

    {
        void *dispatch_context;
        void *dispatch_owner;
        void *dispatch_pos;
        void *handler;

        if (current == (s32)&D_800930E4 || current == (s32)&D_80093250) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_08;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&D_800AA5F8) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_14;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&D_80093328) {
            dispatch_context = context;
            dispatch_owner = owner;
            handler = ((S_7FFFE25C_4 *)(((Rec_D_80082D58 *)context)->unk_58))->unk_0C;
            dispatch_pos = adjusted_pos;
            ((DispatchFn)handler)(dispatch_context, dispatch_owner, dispatch_pos, dispatch_param);
        } else if (current == (s32)&D_80093638) {
            func_8009C340(context, owner, adjusted_pos, dispatch_param);
        } else if (!(current == (s32)&D_80092698 || current == (s32)&D_800927EC ||
            current == (s32)&D_80092A84 || current == (s32)&D_80092FF0 ||
            current == (s32)&D_80092CD4 || current == (s32)&D_80092DA8 ||
            current == (s32)&D_80092ECC || current == (s32)&D_800933FC ||
            current == (s32)&D_80090A6C || func_800352FC() != 0) || previous_owner != (s32)owner) {
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
