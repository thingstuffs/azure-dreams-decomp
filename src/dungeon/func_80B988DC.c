#include "common.h"

extern s32 func_800AB1C0(M2C_UNK);
extern void func_800AD594(s32, s32);
extern void func_800A4ACC(s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_80170E9C;

/* Updates an eligible actor and conditionally resets the entity state. */
void func_801720DC(void *entity_arg, s32 check_context, s32 value_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = value_arg;
    s32 actor = actor_arg;

    if (func_800AB1C0(entity_arg, check_context, value_arg, actor_arg) != 0) {
        func_800AD594(actor, 3);
        func_800A4ACC(actor);
        if ((func_800AD9B4(check_value, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E9C;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
