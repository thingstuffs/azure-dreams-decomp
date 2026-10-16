#include "common.h"

extern s32 dungeonCreateLinkedActorFadeEffect(s32);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalS32;

extern GlobalS32 D_800DF55C;
extern GlobalS32 D_800DF560;

/* Store the lookup result for the adjusted global value and report success. */
s32 dungeonCreateAndStorePendingActorFade(void) {
    s32 result;

    result = dungeonCreateLinkedActorFadeEffect(D_800DF55C.value - 0x20);
    D_800DF560.value = result;
    return result != 0;
}
