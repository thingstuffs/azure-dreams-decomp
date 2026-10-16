#include "common.h"

extern s32 D_80174704;
extern s32 dungeonCreateLinkedActorFadeEffect(s32);

/* Store the object query result and set an active flag and countdown when nonzero. */
s32 dungeonQueryObjectAndSetCountdown(void) {
    s32 result;
    s32 flag;
    void *status;

    status = (void *)(D_80174704 + 0x20);
    result = dungeonCreateLinkedActorFadeEffect(D_80174704);
    *(s32 *)((s8 *)status + 0xA4) = result;
    if (result == 0) {
        return 0;
    }
    flag = 1;
    *(s8 *)((s8 *)status + 0xB0) = flag;
    *(s8 *)((s8 *)status + 0xB1) = 60;
    return flag;
}
