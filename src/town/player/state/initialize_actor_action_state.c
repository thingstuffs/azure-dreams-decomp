#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void dispatch_sound_by_global_flag(void);                            /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
extern void D_8009204C();

typedef struct S_800942B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800942B0_0;   /* arg1 in initialize_actor_action_state */


/* Initializes an object and its associated state. */
void initialize_actor_action_state(Rec_func_80094268_arg0 *object, S_800942B0_0 *state, s32 initData) {
    dispatch_sound_by_global_flag();
    state->unk_14 = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(D_800D00B0, object, (void *)(initData));
    object->unk_00.as_pm = &D_8009204C;
    object->unk_0A.as_s16 = 0;
}
