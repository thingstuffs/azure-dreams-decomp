#include "common.h"

extern s32 create_linked_actor_fade_effect(s32);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalS32;

extern GlobalS32 D_800DF55C;
extern GlobalS32 D_800DF560;

/* Store the lookup result for the adjusted global value and report success. */
s32 create_and_store_pending_actor_fade(void) {
    s32 result;

    result = create_linked_actor_fade_effect(D_800DF55C.value - 0x20);
    D_800DF560.value = result;
    return result != 0;
}
