#include "common.h"

extern s32 func_800AB1C0(void *, s32, s32, s32);
extern void func_800AD594(s32, s32);
extern void func_800A4ACC(s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_80170E94;

/* Update the actor after a successful action and reset the entity script on a positive result. */
void func_8017291C(void *action_entity, s32 action, s32 source_actor, s32 target_actor) {
    void *entity = action_entity;
    s32 source = source_actor;
    s32 actor = target_actor;

    if (func_800AB1C0(action_entity, action, source_actor, target_actor) != 0) {
        func_800AD594(actor, 5);
        func_800A4ACC(actor);
        if ((func_800AD9B4(source, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E94;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
