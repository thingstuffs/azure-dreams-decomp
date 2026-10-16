/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void townInitializeActorActionWithDefaults(void *actor, void *action_id, void *action_state, void *state_data);
extern s32 D_800F8FC0[];

void func_8009CC58(void *context, void *source, void *record) {
    townInitializeActorActionWithDefaults(context, source, record, &D_800F8FC0[0]);
    *(s16 *)((u8 *)record + 0x10) = 0;
    *(u16 *)((u8 *)record + 0x14) = *(u16 *)((u8 *)record + 0x14) | 0x1C;
}
