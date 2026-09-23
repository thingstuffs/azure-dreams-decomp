#include "common.h"

extern void func_8008CBA0(void *, s32, void *, void *);
extern void func_8008CF6C(void *, s32, void *, void *);
extern void func_80097898(void *, s32, void *, void *);
extern void func_80097C50(void *, s32, void *, void *);

extern u16 D_80013714;
extern u8 D_8004F5F4[];
extern s32 D_80082EB0;
extern u8 D_80083160[];
extern s32 D_800E4940;

/* Apply pending actor updates and handle input-driven state transitions. */
void func_80097C78(void *controller, s32 move_state, void *entity, void *actor)
{
    s16 pending_delta = *(s16 *)((u8 *)actor + 0x64);
    u8 *input_state = D_80083160;

    if (pending_delta < 0) {
        *(u16 *)((u8 *)entity + 0x14) &= 0xF7FF;
        func_80097898(controller, move_state, entity, actor);
        return;
    }

    if (pending_delta > 0) {
        func_8008CBA0(controller, move_state, entity, actor);
    }

    if (!(D_80013714 & 1) && (*(s32 *)(input_state + 8) & 0x80)) {
        *(s16 *)((u8 *)actor + 0x8A) = 2;
        D_800E4940 = 2;
        func_8008CF6C(controller, move_state, entity, D_8004F5F4);
        D_80082EB0 = 0;
        *(s32 *)((u8 *)controller + 0xC8) = 0;
        *(s32 *)((u8 *)controller + 0x104) = 0;
        return;
    }

    if (*(u8 *)((u8 *)controller + 0x9A) != 0x3A &&
        (*(s32 *)((u8 *)actor + 0x1C) & 0x200)) {
        *(u16 *)((u8 *)entity + 0x14) &= 0xF7FF;
        func_80097C50(controller, move_state, entity, actor);
    }
}
