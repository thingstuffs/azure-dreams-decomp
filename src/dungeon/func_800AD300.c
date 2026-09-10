#include "common.h"

extern s32 func_80042900(void *, s32);
extern s8 func_8009FB34(u8, u8);
extern s32 func_800A03C4(void *, u8, u8);
extern s32 func_800A1C58(void *);
extern s32 func_800A2C34(s32);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_800ACB98();
extern void func_800B318C(void *, s32, void *, void *);
extern u16 D_80083460[];
extern u16 D_80083462;

/* Dispatch an entity action and update the actor and destination state. */
void func_800B2A60(u8 *actor, s32 action_context, u8 *destination, u8 *target)
{
    u8 *actor_state = actor;
    u8 *entity;
    s32 context = action_context;
    u8 *position = destination;
    u16 *flags = D_80083460;
    u8 *idle_actor = actor;

    do {
        ASM_KEEP(actor_state);
    } while (0);

    if (!(flags[1] & 0x1000)) {
        entity = target;
        if (*(u8 *)(entity + 0x25) == 0) {
            *(s8 *)(actor_state + 0xAD) = 0;
            func_800ACB98(idle_actor);
            return;
        }

        if ((func_80042900(entity, 1) << 16) == 0) {
            if (!(flags[1] & 0x2000)) {
                if (*(s32 *)(entity + 0x1C) & 0x100) {
                    func_800AA258(actor_state, context, position, entity);
                    return;
                }

                if (*(u8 *)(actor_state + 0x9A) != 0xE) {
                    *(u8 *)(actor_state + 0x9A) = 0xE;
                }
                *(u16 *)(actor_state + 0x98) &= 0xFFF3;

                if ((*(s16 *)(entity + 0x64) != 0) &&
                    (func_800AA6B4(actor_state, context, position, 0) != 0)) {
                    return;
                }

                if (*(s32 *)(entity + 0x1C) & 0x80000) {
                    func_800AA888(actor_state, context, position, entity);
                    func_800B318C(actor_state, context, position, entity);
                    return;
                }

                if ((func_800A1C58(entity) << 16) != 0) {
                    goto fail;
                }
            }

            *(s8 *)(position + 0x26) = func_8009FB34(*(u8 *)(position + 0x24),
                                                  *(u8 *)(position + 0x25));
            if (*(s8 *)(entity + 0x6D) <= 0) {
                goto done;
            }
            if (D_80083462 & 0x1000) {
                goto done;
            }
            if ((func_800A2C34(0) << 16) != 0) {
                goto done;
            }
            if (func_800A03C4(entity, *(u8 *)(position + 0x24),
                              *(u8 *)(position + 0x25)) == 0) {
                goto clear;
            }
        }

fail:
        *(s8 *)(actor_state + 0xAD) = 0;
        func_800ACB98(actor_state, context, position, entity);
        return;

clear:
        *(s8 *)(entity + 0x6D) = 0;
    }

done:
    return;
}
