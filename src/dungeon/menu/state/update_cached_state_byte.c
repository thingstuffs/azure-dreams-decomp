#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"


typedef struct S_800DC5B4_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_800DC5B4_0;   /* *state in update_cached_state_byte */

typedef struct S_800DC5B4_1 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_800DC5B4_1;   /* arg0 in update_cached_state_byte */

/* Processes a change in the global state value and updates the cached value. */
void update_cached_state_byte(S_800DC5B4_1 *cachedState) {
    u8 currentValue;
    void **globalStateSlot;

    globalStateSlot = (void **)(&primary_actor_record);
    currentValue = ((S_800DC5B4_0 *)(*globalStateSlot))->unk_11;
    if (currentValue != cachedState->unk_30) {
        draw_filler_first_number(currentValue, cachedState->unk_30, 2, 0x18A, 0x190, 0);
        cachedState->unk_30 = ((S_800DC5B4_0 *)(*globalStateSlot))->unk_11;
    }
}
