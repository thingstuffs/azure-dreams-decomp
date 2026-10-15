/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void func_8009CB64(void *actor, void *action_id, void *action_state, void *state_data);
extern s32 D_800F8FD8[];

void func_8009CC98(void *context, void *source, void *record) {
    func_8009CB64(context, source, record, &D_800F8FD8[0]);
    *(s16 *)((u8 *)record + 0x10) = 0;
    *(u16 *)((u8 *)record + 0x14) = *(u16 *)((u8 *)record + 0x14) | 0x1C;
}
