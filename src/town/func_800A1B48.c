#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/dungeon_delay_views.h"

   /* arg2 in update_the_target_offset_advance_phase_handle_active_event */


short SD_Call(int flags);
s32 func_800644B8();                             /* extern */
void initialize_the_town_entity_synchronize_slot_state(); /* extern */
typedef struct AllocatedObject AllocatedObject;
AllocatedObject *allocate_object_with_callbacks();                      /* extern */
void check_adjusted_input_indices();                      /* extern */
extern s32 D_800834B8;
extern M2C_UNK D_800935BC;
extern s32 D_800CFCC4;

/* Update the target offset, advance the phase, and handle the active event. */
void update_the_target_offset_advance_phase_handle_active_event(void *state, s32 event_id, DelayMotionZ *target, s32 context) {
    s32 active_event;

    target->unk_08 = (s32) (((Rec_func_80094268_arg0 *)state)->unk_A0
        + (func_800644B8(((Rec_func_80094268_arg0 *)state)->unk_6C.as_s16) << 7));
    (*(s16 *)((u8 *)state + 0x6C)) = (s16) ((u16) ((Rec_func_80094268_arg0 *)state)->unk_6C.as_s16 + 0x40);
    active_event = D_800CFCC4;
    if ((active_event == event_id) && (D_800834B8 == &D_800935BC)) {
        check_adjusted_input_indices(target);
        allocate_object_with_callbacks(target);
        SD_Call(0x513);
        initialize_the_town_entity_synchronize_slot_state(state, active_event, target, context);
    }
}
