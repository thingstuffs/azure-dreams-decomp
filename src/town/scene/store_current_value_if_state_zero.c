#include "shared/town_event_state.h"
#include "common.h"

typedef struct S_8001B960_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001B960_0;   /* obj in store_current_value_if_state_zero */

   /* (index * 0x10) + ((S_8001B960_0 *)obj)->unk_10 in store_current_value_if_state_zero */


extern s32 build_three_value_block(void);

/* Store the current handler in the object's table slot unless the global gate is set. */
s32 store_current_value_if_state_zero(S_8001B960_0 *obj, s32 index) {
    if (town_event_state->unk_05 == 0) {
        ((TownEventEntryValueView *)((index * 0x10) + obj->unk_10))->unk_08 =
            build_three_value_block();
        return 0;
    }
    return 1;
}
