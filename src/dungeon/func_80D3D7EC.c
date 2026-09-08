#include "common.h"

extern u32 func_800AB1C0(void);
extern void func_800AD594(void *, s32);
extern void func_800A4ACC(void *);
extern s32 func_800AD9B4(void *, void *);

extern u16 D_80083462[];
extern u8 D_80171A80[];

/* Updates actor behavior and state fields according to mode and input. */
void func_80172FEC(void *state, s32 unused, void *action_arg, void *actor_arg)
{
    void *action_data = action_arg;
    void *actor = actor_arg;

    if (func_800AB1C0() != 0) {
        if (*(u8 *)((u8 *)state + 0xB5) == 0) {
            func_800AD594(actor, 4);
            func_800A4ACC(actor);
            if ((func_800AD9B4(action_data, actor) << 16) <= 0) {
                return;
            }
        } else {
            func_800AD594(actor, 0x10);
            func_800A4ACC(actor);
        }
        *(void **)((u8 *)state + 0x8C) = D_80171A80;
    }

    if (D_80083462[0] & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
        if (*(u8 *)((u8 *)state + 0xB5) != 0) {
            *(s16 *)((u8 *)state + 0x92) = 0;
        }
    }
}
