#include "common.h"
#include "shared/town_handler.h"

void update_actor_with_periodic_effect(); /* extern */
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
void update_actor_with_periodic_effect(Rec_func_80094268_arg0 *actor, EntityRec *position, s32 context);
extern u8 D_800D0158;

typedef struct S_80091990_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80091990_0;   /* arg2 in reset_action_handler_on_flag */

/* Resets the handler when state flags are set, then invokes the base handler. */
void reset_action_handler_on_flag(s32 **handler_slot, s32 context, S_80091990_0 *state) {
    if (state->unk_14 & 0x6000) {
        call_the_handler_selects_nonzero_entry((s32 *) &D_800D0158, (Rec_func_80094268_arg0 *) handler_slot, state);
        *handler_slot = &update_actor_with_periodic_effect;
    }
    update_actor_with_periodic_effect(handler_slot, context, state);
}
